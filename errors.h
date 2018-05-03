//Created by dopieralad on 2018/04/26.

#ifndef OPENGL_ARCANOID_ERRORS_H
#define OPENGL_ARCANOID_ERRORS_H

/**
 * Namespace for handling errors and possibly
 * fixing the game's state after an error occurs.
 *
 * As we need only static methods it's much simpler to use a namespace
 * instead of a class with static methods inside.
 */
namespace Errors {
	/**
	 * Handles errors generated by OpenGL.
	 *
	 * @param exit_code OpenGL error code.
	 * @param details OpenGL error description.
	 */
	void opengl_error_callback(int exit_code, const char* details);

	/**
	 * Handles a fatal error and exits the application.
	 *
	 * @param exit_code An error code that the application will return upon exit.
	 * @param details A message describing the error.
	 */
	void handle_fatal(int exit_code, const char* details);

	/**
	 * Handles a fatal error and exits the application.
	 *
	 * @param details A message describing the error.
	 */
	void handle_fatal(const char* details);
}
#endif //OPENGL_ARCANOID_ERRORS_H