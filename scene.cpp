// Created by dopieralad on 2018/04/26.

#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include "scene.h"
#include "errors.h"

Scene::Scene() {
	init();
}

void Scene::init() {
	//Register OpenGL error handling procedure
	glfwSetErrorCallback(Errors::opengl_error_callback);

	//Initialize GLFW library
	if (!glfwInit()) {
		Errors::handle_fatal("Could not initialize GLFW library!\n");
	}

	//Create a 500 by 500 window and OpenGL context
	window = glfwCreateWindow(500, 500, "Arkanoid", nullptr, nullptr);

	//Close program if window could not be created
	if (!window) {
		deinit();
		Errors::handle_fatal("Could not create OpenGL window!\n");
	}

	//Make window active
	glfwMakeContextCurrent(window);
	//Wait for screen synchronization signal before swapping buffers (VSync)
	glfwSwapInterval(1);

	//Initialize GLEW library
	GLenum initOutcome;
	if ((initOutcome = glewInit()) != GLEW_OK) {
		deinit();
		fprintf(stderr, "GLEW library initialization error: %s\n", glewGetErrorString(initOutcome));
		Errors::handle_fatal("Could not initialize GLEW library!\n");
	}
}

void Scene::run() {
	//As long as window is not closed
	while (!glfwWindowShouldClose(window)) {
		//Handle external events
		glfwPollEvents();
	}
}

void Scene::deinit() {
	//Delete OpenGL context and the window
	glfwDestroyWindow(window);
	//Release GLFW resources
	glfwTerminate();
}

Scene::~Scene() {
	deinit();
}
