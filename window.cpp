// Created by dopieralad on 2018/04/26.

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include "window.h"
#include "errors.h"

Window* Window::instance = nullptr;

Window* Window::get() {
	if (Window::instance == nullptr) {
		Window::instance = new Window();
	}

	return Window::instance;
}

void Window::init() {
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
	//Wait for screen synchronization signal before swapping buffers (VSync)
	glfwSwapInterval(1);

	//Initialize GLEW library
	GLenum initOutcome;
	if ((initOutcome = glewInit()) != GLEW_OK) {
		deinit();
		fprintf(stderr, "GLEW library initialization error: %s\n", glewGetErrorString(initOutcome));
		Errors::handle_fatal("Could not initialize GLEW library!\n");
	}

	//Configure the window
	Window::configure();
}

void Window::configure() {
	//Clear screen with black
	glClearColor(0, 0, 0, 1); //Czyść ekran na czarno

	//Turn on Z-buffer usage
	glEnable(GL_DEPTH_TEST);

	//Register window resize event handler
	glfwSetFramebufferSizeCallback(glWindow, Window::resize);

	//Register window key event handler
	glfwSetKeyCallback(glWindow, Window::handle_key);
}

void Window::show() {
	//As long as window is not closed
	while (!glfwWindowShouldClose(glWindow)) {
		//Handle external events
		glfwPollEvents();
	}
}

void Window::deinit() {
	//Delete OpenGL context and the windows
	glfwDestroyWindow(glWindow);

	//Release GLFW resources
	glfwTerminate();

	//Delete this window
	delete this;

	//Clear the instance pointer
	Window::instance = nullptr;
}

void Window::resize(GLFWwindow* window, int width, int height) {
	//Generate window with new viewport resolution
	glViewport(0, 0, width, height);
}

void Window::handle_key(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void Window::draw() {
	//Clear color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Swap buffers
	glfwSwapBuffers(glWindow);
}
