// Created by dopieralad on 2018/04/26.

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "game.h"
#include "errors.h"
#include "constants.h"
#include "models/paddle/paddle.h"
#include "models/brick/brick.h"
#include "models/ball/ball.h"
#include "utils/does_collide.h"
#include "utils/bounce.h"
#include "models/horizontal-wall/horizontal-wall.h"
#include "models/vertical-wall/vertical-wall.h"
#include <vector>
#include <algorithm>

static float padX = 0;
static float cameraRotation = 0;

static const int BRICKS_COUNT = 5;

Game* Game::instance = nullptr;

Game* Game::get() {
	//Create new game if it does not exist yet
	if (Game::instance == nullptr) {
		Game::instance = new Game();
	}

	return Game::instance;
}

void Game::init() {
	//Disable standard out buffering
	setbuf(stdout, nullptr);

	//Register OpenGL error handling procedure
	glfwSetErrorCallback(Errors::opengl_error_callback);

	//Initialize GLFW library
	if (!glfwInit()) {
		Errors::handle_fatal("Could not initialize GLFW library!\n");
	}

	//Create a 500 by 500 window and OpenGL context
	glWindow = glfwCreateWindow(500, 500, "Arkanoid", nullptr, nullptr);

	//Close program if window could not be created
	if (!glWindow) {
		deinit();
		Errors::handle_fatal("Could not create OpenGL window!\n");
	}

	//Make window active
	glfwMakeContextCurrent(glWindow);
	//Maximize the window
	glfwMaximizeWindow(glWindow);
	//Initialize the aspect according to window's dimensions
	windowAspect = 1;
	//Wait for screen synchronization signal before swapping buffers (VSync)
	glfwSwapInterval(1);

	//Initialize GLEW library
	GLenum initOutcome;
	if ((initOutcome = glewInit()) != GLEW_OK) {
		deinit();
		fprintf(stderr, "GLEW library initialization error: %s\n", glewGetErrorString(initOutcome));
		Errors::handle_fatal("Could not initialize GLEW library!\n");
	}

	//Compile and instantiate the shader
	shader = new Shader("shader/vshader.vert", nullptr, "shader/fshader.frag");
	//Use loaded shader
	shader->use();

	//Clear screen with black
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//Turn on Z-buffer usage
	glEnable(GL_DEPTH_TEST);

	//Register window resize event handler
	glfwSetFramebufferSizeCallback(glWindow, Game::resize);

	//Register window key event handler
	glfwSetKeyCallback(glWindow, Game::handle_key);

	//Set camera position
	cameraPosition = glm::vec3(0.0f, 5.0f, 30.0f);

	//Create models
	paddle = new Paddle();

	ball = new Ball();
	ball->setSpeedX(BALL_SPEED);
	ball->setSpeedY(BALL_SPEED);

	// Instantiate and place the bricks
	for (int i = 0; i < BRICKS_COUNT; i++) {
		bricks.push_back(new Brick());
	}

	glm::mat4 brickMatrix;
	int brickOffset;
	for (int i = 0; i < bricks.size(); i++) {
		brickOffset = i - 2;

		brickMatrix = bricks.at(i)->getMatrix();
		brickMatrix = glm::translate(brickMatrix, glm::vec3(brickOffset * 4.0f, 6.0f, 0.0f));
		bricks.at(i)->setMatrix(brickMatrix);
	}

	// Instantiate and place walls
	// Upper wall
	upperWall = new HorizontalWall();
	upperWall->translate(glm::vec3(0.0f, 19.0f, 0.0f));

	// Side walls
	VerticalWall* leftWall = new VerticalWall();
	leftWall->translate(glm::vec3(-11.0f, 10.0f, 0.0f));
	sideWalls.push_back(leftWall);

	VerticalWall* rightWall = new VerticalWall();
	rightWall->translate(glm::vec3(11.0f, 10.0f, 0.0f));
	sideWalls.push_back(rightWall);
}

void Game::run() {
	//As long as window is not closed
	while (!glfwWindowShouldClose(glWindow)) {
		//Reset game timer
		resetTimer();

		//Recalculate game's state
		recalculate();

		//Draw all objects
		draw();

		//Handle external events
		glfwPollEvents();
	}
}

void Game::deinit() {
	//Delete this window
	delete this;
}

void Game::resize(GLFWwindow* window, int width, int height) {
	//Generate window with new viewport resolution
	glViewport(0, 0, width, height);

	//Update window resolution aspect
	if (height != 0) {
		Game::get()->windowAspect = (float) width / (float) height;
	} else {
		Game::get()->windowAspect = 1;
	}
}

void Game::handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_LEFT) {
			padX = -1;
		} else if (key == GLFW_KEY_RIGHT) {
			padX = 1;
		} else if (key == GLFW_KEY_A) {
			cameraRotation = -1;
		} else if (key == GLFW_KEY_D) {
			cameraRotation = 1;
		}
	} else if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_LEFT && padX == -1) {
			padX = 0;
		} else if (key == GLFW_KEY_RIGHT && padX == 1) {
			padX = 0;
		} else if (key == GLFW_KEY_A || key == GLFW_KEY_D) {
			cameraRotation = 0;
		}
	}
}

void Game::resetTimer() {
	//Get current time
	time = glfwGetTime();

	//Clear timer
	glfwSetTime(0);

	//Print out FPS
	//printf("\rFPS: %f", 1 / time);
}

void Game::recalculatePaddle() {
	//Accelerate the paddle
	paddle->setSpeedX(paddle->getSpeedX() + padX * PAD_ACCELERATION * time);

	//Keep pad maximum speed
	paddle->setSpeedX(std::min(paddle->getSpeedX(), PAD_MAX_SPEED));

	//Update paddle's position according to it's speed
	paddle->translate(glm::vec3(paddle->getSpeedX() * time, 0.0f, 0.0f));

	//Keep paddle between side walls
	auto paddleBoundingBox = paddle->getBoundingBox();
	if (paddleBoundingBox->getMaxX() > 10.0f) {
		paddle->setSpeedX(0.0f);
		paddle->translate(glm::vec3(10.0f - paddleBoundingBox->getMaxX(), 0.0f, 0.0f));
	} else if (paddleBoundingBox->getMinX() < -10.0f) {
		paddle->setSpeedX(0.0f);
		paddle->translate(glm::vec3(-10.0f - paddleBoundingBox->getMinX(), 0.0f, 0.0f));
	}

	//Apply regression to paddle's speed
	double paddleSpeedX = paddle->getSpeedX();
	int speedSign = paddleSpeedX > 0 ? 1 : -1;
	paddleSpeedX = std::abs(paddleSpeedX); //Use absolute value to avoid checking for negative values
	double paddleRegression = std::max(paddleSpeedX * PAD_REGRESSION * time, PAD_MIN_REGRESSION); //Compute actual regression
	double paddleSpeedDecrease = std::min(paddleRegression, paddleSpeedX); //Avoid accelerating due to regression
	paddleSpeedX = paddleSpeedX - paddleSpeedDecrease; //Decrease the speed
	paddle->setSpeedX(paddleSpeedX * speedSign); //Set the speed with the original sign
}

void Game::recalculate() {
	//Compute perspective matrix
	perspectiveMatrix = glm::perspective(50 * PI / 180, windowAspect, 1.0f, 50.0f);

	//Recalculate camera position
	cameraPosition = glm::rotate(cameraPosition, (float) (CAMERA_SPEED * time * cameraRotation), glm::vec3(0.0f, 1.0f, 0.0f));

	//Compute view matrix
	viewMatrix = glm::lookAt(
			cameraPosition,
			glm::vec3(0.0f, 10.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
	);

	recalculatePaddle();

	// Recalculate ball position
	glm::mat4 ballMatrix = ball->getMatrix();
	std::vector<Model*> hitObjects;
	std::vector<Brick*> destroyedBricks;

	for (Brick* brick : bricks) {
		if (doesCollide(ball, brick)) {
			printf("Collides with brick!\n");
			hitObjects.push_back(brick);

			destroyedBricks.push_back(brick);
		}
	}
	if (doesCollide(ball, paddle)) {
		printf("Collides with paddle!\n");
		hitObjects.push_back(paddle);
	}

	// walls
	if (doesCollide(ball, upperWall)) {
		printf("Collides with upper wall!\n");
		hitObjects.push_back(upperWall);
	}
	for (VerticalWall* sideWall : sideWalls) {
		if (doesCollide(ball, sideWall)) {
			printf("Collides with side wall!\n");
			hitObjects.push_back(sideWall);
		}
	}

	for (Model* hitObject : hitObjects) {
		bounce(ball, hitObject);
	}

	for (Brick* destroyedBrick : destroyedBricks) {
		auto vectorBeginning = bricks.begin();
		auto vectorEnd = bricks.end();
		auto brickPosition = std::find(vectorBeginning, vectorEnd, destroyedBrick);

		if (brickPosition != vectorEnd) { // Given brick was found in the vector
			auto distance = std::distance(vectorBeginning, brickPosition);
			bricks.erase(vectorBeginning + distance);
			printf("Destroyed brick with index: '%td'!\n", distance);
		}
	}

	ball->translate(glm::vec3(ball->getSpeedX() * time, ball->getSpeedY() * time, 0.0f));
}

void Game::draw() {
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw paddle
	drawModel(paddle);
	drawModel(ball);
	for (Brick* brick : bricks) {
		drawModel(brick);
	}
	drawModel(upperWall);
	for (VerticalWall* sideWall : sideWalls) {
		drawModel(sideWall);
	}

	//Swap buffers
	glfwSwapBuffers(glWindow);
}

void Game::drawModel(Model* model) {
	//Pass all matrices to the shader
	glUniformMatrix4fv(shader->getUniformLocation("P"), 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("V"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("M"), 1, GL_FALSE, glm::value_ptr(model->getMatrix()));

	//Enable attributes
	glEnableVertexAttribArray(shader->getAttribLocation("vertex"));
	glEnableVertexAttribArray(shader->getAttribLocation("color"));
	glEnableVertexAttribArray(shader->getAttribLocation("normal"));

	//Pass attributes to the shader
	glVertexAttribPointer(shader->getAttribLocation("vertex"), 4, GL_FLOAT, GL_FALSE, 0, model->getVertices());
	glVertexAttribPointer(shader->getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, 0, model->getColors());
	glVertexAttribPointer(shader->getAttribLocation("normal"), 4, GL_FLOAT, GL_FALSE, 0, model->getNormals());

	//Draw the object
	glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

	//Clean up
	glDisableVertexAttribArray(shader->getAttribLocation("vertex"));
	glDisableVertexAttribArray(shader->getAttribLocation("color"));
	glDisableVertexAttribArray(shader->getAttribLocation("normal"));
}

Game::~Game() {
	//Release the shader
	delete shader;

	//Delete OpenGL context and the windows
	glfwDestroyWindow(glWindow);

	//Release GLFW resources
	glfwTerminate();

	//Clear the instance pointer
	Game::instance = nullptr;
}
