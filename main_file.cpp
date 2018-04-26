#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <cstdio>

#include "scene.h"
#include "errors.h"

int main() {
	auto* scene = new Scene();
	scene->run();
	delete scene;
}
