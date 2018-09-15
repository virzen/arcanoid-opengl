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
#include <string>
#include "glm/gtx/string_cast.hpp"

using std::string;

static float padX = 0;
static float cameraRotation = 0;

const string A = "1111100110011111100110011001";
const string R = "1110100110011110100110011001";
const string K = "1001101010101100110010101001";
const string N = "1001100110011101101110011001";
const string O = "1111100110011001100110011111";
const string I = "0110011001100110011001100110";
const string D = "1110100110011001100110011110";

static const string TEXT_ARR[] = {A, R, K, A, N, O, I, D};
std::vector<string> TEXT(TEXT_ARR, TEXT_ARR + sizeof(TEXT_ARR) / sizeof(TEXT_ARR[0]) );

const float BRICK_SIZE = 2.0f;
const int LETTER_WIDTH_BLOCKS = 4;
const int LETTER_HEIGHT_BLOCKS = 7;
const float LETTER_WIDTH = BRICK_SIZE * LETTER_WIDTH_BLOCKS;
const float LETTER_HEIGHT = BRICK_SIZE * LETTER_HEIGHT_BLOCKS;
const float LETTER_SPACING = 1.0f;

const float TEXT_WIDTH = TEXT.size() * (LETTER_WIDTH + LETTER_SPACING * 2);

const float UPPER_WALL_WIDTH = 20.0f;
const float UPPER_WALLS_NUMBER = ceil(TEXT_WIDTH / UPPER_WALL_WIDTH);

const float SIDE_WALL_WIDTH = 2.0f;
const float SIDE_WALL_HEIGHT = 20.0f;
const float SIDE_WALL_DISTANCE_FROM_CENTER = (UPPER_WALLS_NUMBER * UPPER_WALL_WIDTH / 2) + (SIDE_WALL_WIDTH / 2);

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
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Turn on Z-buffer usage
	glEnable(GL_DEPTH_TEST);

	//Register window resize event handler
	glfwSetFramebufferSizeCallback(glWindow, Game::resize);

	//Register window key event handler
	glfwSetKeyCallback(glWindow, Game::handle_key);

	//Set camera position
	cameraPosition = glm::vec3(0.0f, 10.0f, 60.0f);

	startNewGame();
}

void Game::startNewGame() {
	//Create models
	paddle = new Paddle();

	ball = new Ball();
	ball->setSpeedX(BALL_SPEED);
	ball->setSpeedY(BALL_SPEED);

	createBricks();

	createWalls();
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
	float distanceToLeftSideWall = -1 * (SIDE_WALL_DISTANCE_FROM_CENTER - SIDE_WALL_WIDTH / 2);
	float distanceToRightSideWall = SIDE_WALL_DISTANCE_FROM_CENTER - SIDE_WALL_WIDTH / 2;
	auto paddleBoundingBox = paddle->getBoundingBox();

	if (paddleBoundingBox->getMaxX() > distanceToRightSideWall) {
		paddle->setSpeedX(0.0f);
		paddle->translate(glm::vec3(distanceToRightSideWall - paddleBoundingBox->getMaxX(), 0.0f, 0.0f));
	} else if (paddleBoundingBox->getMinX() < distanceToLeftSideWall) {
		paddle->setSpeedX(0.0f);
		paddle->translate(glm::vec3(distanceToLeftSideWall - paddleBoundingBox->getMinX(), 0.0f, 0.0f));
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
	perspectiveMatrix = glm::perspective(50 * PI / 180, windowAspect, 1.0f, 150.0f);

	//Recalculate camera position
	cameraPosition = glm::rotate(cameraPosition, (float) (CAMERA_SPEED * time * cameraRotation), glm::vec3(0.0f, 1.0f, 0.0f));

	//Compute view matrix
	viewMatrix = glm::lookAt(
			cameraPosition,
			glm::vec3(0.0f, 15.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
	);

	recalculatePaddle();


	// Finish game when ball below paddle
	auto paddleBoundingBox = paddle->getBoundingBox();
	auto ballBoundingBox = ball->getBoundingBox();

	if (ballBoundingBox->getMaxY() < paddleBoundingBox->getMinY()) {
		startNewGame();
	}


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
	for (HorizontalWall* upperWall : upperWalls) {
		if (doesCollide(ball, upperWall)) {
			printf("Collides with upper wall!\n");
			hitObjects.push_back(upperWall);
		}
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

void Game::createBricks() {
	// Clear bricks from previous game
	bricks.clear();

	for (int letterIndex = 0; letterIndex < TEXT.size(); letterIndex++) {
		string letter = TEXT.at(letterIndex);

		float letterOffset = (float) letterIndex - floor(TEXT.size() / 2.0f) + 0.5f;
		glm::vec3 letterTranslationVector = glm::vec3((letterOffset * (LETTER_WIDTH + LETTER_SPACING * 2)), 20.0f, 0.0f);

		for (int brickIndex = 0; brickIndex < letter.length(); brickIndex++) {
			float positionX = brickIndex % LETTER_WIDTH_BLOCKS;
			float positionY = floor(brickIndex / LETTER_WIDTH_BLOCKS);
			bool isBrickPresent = letter[brickIndex] == '1';

			if (!isBrickPresent) {
				continue;
			}

			Brick* brick = new Brick();
			glm::mat4 brickMatrix = brick->getMatrix();

			brickMatrix = glm::translate(brickMatrix, letterTranslationVector);

			// what is -1.5f?
			float xTranslation = -1.5f * BRICK_SIZE +  positionX * BRICK_SIZE; 
			float yTranslation = 3.0f * BRICK_SIZE - positionY * BRICK_SIZE;
			glm::vec3 brickTranslationVector = glm::vec3(xTranslation, yTranslation, 0.0f);
			brickMatrix = glm::translate(brickMatrix, brickTranslationVector);

			brick->setMatrix(brickMatrix);

			bricks.push_back(brick);
		}
	}
}

void Game::createWalls() {
	// clear walls from previous game
	upperWalls.clear();
	sideWalls.clear();

	// Instantiate and place walls
	// Upper wall
	for (int i = 0; i < UPPER_WALLS_NUMBER; i++) {
		upperWalls.push_back(new HorizontalWall());
	}

	for (int upperWallIndex = 0; upperWallIndex < upperWalls.size(); upperWallIndex++) {
		HorizontalWall* upperWall = upperWalls.at(upperWallIndex);

		float upperWallOffset = (float) upperWallIndex - floor(upperWalls.size() / 2.0f) + 0.5f;
		float upperWallX = (upperWallOffset * UPPER_WALL_WIDTH);

		upperWall->translate(glm::vec3(upperWallX, 39.0f, 0.0f));
	}

	// Side walls
	std::vector<VerticalWall*> leftWalls;
	leftWalls.push_back(new VerticalWall());
	leftWalls.push_back(new VerticalWall());

	for (int leftWallIndex = 0; leftWallIndex < leftWalls.size(); leftWallIndex++) {
		VerticalWall* leftWall = leftWalls.at(leftWallIndex);

		float leftWallX = -1 * SIDE_WALL_DISTANCE_FROM_CENTER;
		float leftWallY = leftWallIndex * SIDE_WALL_HEIGHT + 10.0f;

		leftWall->translate(glm::vec3(leftWallX, leftWallY, 0.0f));

		sideWalls.push_back(leftWall);
	}

	std::vector<VerticalWall*> rightWalls;
	rightWalls.push_back(new VerticalWall());
	rightWalls.push_back(new VerticalWall());

	for (int rightWallIndex = 0; rightWallIndex < rightWalls.size(); rightWallIndex++) {
		VerticalWall* rightWall = rightWalls.at(rightWallIndex);

		float rightWallX = SIDE_WALL_DISTANCE_FROM_CENTER;
		float rightWallY = rightWallIndex * SIDE_WALL_HEIGHT + 10.0f;

		rightWall->translate(glm::vec3(rightWallX, rightWallY, 0.0f));

		sideWalls.push_back(rightWall);
	}
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

	for (HorizontalWall* upperWall : upperWalls) {
		drawModel(upperWall);
	}
	for (VerticalWall* sideWall : sideWalls) {
		drawModel(sideWall);
	}

	//Swap buffers
	glfwSwapBuffers(glWindow);
}

void Game::drawModel(Model* model) {
	//Pass all matrices to the shader
	glUniformMatrix4fv(shader->getUniformLocation("perspectiveMatrix"), 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(model->getMatrix()));

	//Enable attributes
	glEnableVertexAttribArray(shader->getAttribLocation("vertexCoordinates"));
	glEnableVertexAttribArray(shader->getAttribLocation("vertexColor"));
	glEnableVertexAttribArray(shader->getAttribLocation("vertexNormal"));

	//Pass attributes to the shader
	glVertexAttribPointer(shader->getAttribLocation("vertexCoordinates"), 4, GL_FLOAT, GL_FALSE, 0, model->getVertices());
	glVertexAttribPointer(shader->getAttribLocation("vertexColor"), 4, GL_FLOAT, GL_FALSE, 0, model->getColors());
	glVertexAttribPointer(shader->getAttribLocation("vertexNormal"), 4, GL_FLOAT, GL_FALSE, 0, model->getNormals());

	//Draw the object
	glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

	//Clean up
	glDisableVertexAttribArray(shader->getAttribLocation("vertexCoordinates"));
	glDisableVertexAttribArray(shader->getAttribLocation("vertexColor"));
	glDisableVertexAttribArray(shader->getAttribLocation("vertexNormal"));
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
