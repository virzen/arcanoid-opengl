// Created by dopieralad on 2018/04/26.

#ifndef GRAPHICS_OPENGL_PROJECT_SCENE_H
#define GRAPHICS_OPENGL_PROJECT_SCENE_H

#include <GLFW/glfw3.h>

/**
 * A singleton class representing the main and only window of the game.
 */
class Window {

public:
	/**
	 * Gets the one and only one instance of a Window.
	 *
	 * @return  A Window's instance.
	 */
	static Window* get();

	/**
	 * Initializes the window.
	 */
	void init();

	/**
	 * Shows the window and its contents.
	 * This method is synchronous and will end only if the window is closed.
	 */
	void show();

	/**
	 * Releases all resources allocated by this window, including Window's instance.
	 *
	 * NOTE: Be careful as this method will also delete the object,
	 * so further references to this object will cause failure.
	 */
	void deinit();

private:
	/**
	 * This static field stores the only Window instance.
	 */
	static Window* instance;

	/**
	 * This method handles window resize events.
	 *
	 * @param window A pointer to the resized window.
	 * @param width New width of the window.
	 * @param height New height of the window.
	 */
	static void resize(GLFWwindow* window, int width, int height);

	/**
	 * This method handles key press and release events.
	 *
	 * @param window A pointer to the window where the event occurred.
	 * @param key A code of a pressed or released key.
	 * @param scancode System-specific scancode of the key.
	 * @param action Cde of an action to distinguish between presses and releases.
	 * @param mods Bit-code of modifier keys pressed along with the main key (CTRL, ALT, SHIFT).
	 */
	static void handle_key(GLFWwindow* window, int key, int scancode, int action, int mods);

	/**
	 * An instance of active OpenGL window.
	 */
	GLFWwindow* glWindow;

	/**
	 * Private no-arg constructor to disallow instantiating
	 * this class as it should be a singleton.
	 */
	Window() = default;

	/**
	 * Configures this window.
	 */
	void configure();

	/**
	 * Draws this window's contents.
	 */
	void draw();
};


#endif //GRAPHICS_OPENGL_PROJECT_SCENE_H
