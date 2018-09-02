#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <cstdio>

#include "game.h"
#include "errors.h"

/**
 * Runs the Arkanoid application.
 *
 * @param argc Number of arguments passed.
 * @param argv An array of arguments.
 * @return Application's exit code.
 */
int main(int argc, char* argv[]) {
	//Get game's instance
	Game* game = Game::get();

	//Initialize the game
	game->init();

	//Start the game
	game->run();

	//Deinitialize the game
	game->deinit();
}
