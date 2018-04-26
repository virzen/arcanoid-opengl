#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <cstdio>

#include "window.h"
#include "errors.h"

int main() {
	//Get window's instance
	Window* window = Window::get();

	//Initialize the window
	window->init();

	//Show the window
	window->show();

	//Deconstruct the window
	window->deinit();
}
