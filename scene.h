// Created by dopieralad on 2018/04/26.

#ifndef GRAPHICS_OPENGL_PROJECT_SCENE_H
#define GRAPHICS_OPENGL_PROJECT_SCENE_H


#include <GLFW/glfw3.h>

class Scene {

public:
	Scene();
	void init();
	void run();
	void deinit();
	~Scene();

private:
	GLFWwindow* window;
};


#endif //GRAPHICS_OPENGL_PROJECT_SCENE_H
