// Created by dopieralad on 2018/04/26.

#ifndef OPENGL_ARCANOID_GAME_H
#define OPENGL_ARCANOID_GAME_H

#include <GLFW/glfw3.h>
#include "shader/shader.h"
#include "models/model.h"
#include "constants.h"
#include "models/paddle/paddle.h"
#include "models/brick/brick.h"
#include <vector>

/**
 * A singleton class representing the game instance.
 */
class Game {

public:
	/**
	 * Gets the one and only one instance of the game.
	 *
	 * @return  A game's instance.
	 */
	static Game* get();

	/**
	 * Initializes the game.
	 */
	void init();

	/**
	 * Shows the window and its contents.
	 * This method is synchronous and will end only if the window is closed.
	 */
	void run();

	/**
	 * Releases all resources allocated for this game.
	 *
	 * NOTE: Be careful as this method will also delete the object,
	 * so further references to this object will cause failure.
	 */
	void deinit();

private:
	/**
	 * This static field stores the only game's instance.
	 */
	static Game* instance;

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
	 * Aspect of window's dimensions.
	 */
	float windowAspect;
	/**
	 * Game's shader.
	 * Currently only one shader is supported.
	 */
	Shader* shader;
	/**
	 * Time taken to draw last game's frame.
	 */
	double time;
	/**
	 * A perspective matrix.
	 */
	glm::mat4 perspectiveMatrix;
	/**
	 * Camera's position in Eulerian coordinate system.
	 */
	glm::vec3 cameraPosition;
	/**
	 * A matrix representing camera's position and rotation.
	 */
	glm::mat4 viewMatrix;
	/**
	 * An Arkanoid paddle model.
	 */
	Paddle* paddle;

	std::vector<Brick*> bricks;

	/**
	 * Private no-arg constructor to disallow instantiating
	 * this class as it should be a singleton.
	 */
	Game() = default;

	/**
	 * Deconstructor that releases all game's resources.
	 */
	virtual ~Game();

	/**
	 * Resets iteration timer.
	 *
	 * Stores time taken to draw last frame in the 'time' variable.
	 */
	void resetTimer();

	/**
	 * Draws screen contents.
	 */
	void draw();

	/**
	 * Draws given model on the screen.
	 *
	 * @param model A model to draw.
	 */
	void drawModel(Model* model);

	/**
	 * Recalculates positions of game's models.
	 */
	void recalculate();
};


#endif //OPENGL_ARCANOID_GAME_H
