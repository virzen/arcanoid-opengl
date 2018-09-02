//Created by dopieralad on 2018/04/26.

#ifndef OPENGL_ARCANOID_SHADER_H
#define OPENGL_ARCANOID_SHADER_H


#include <GL/glew.h>

class Shader {

public:
	Shader(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile);

	/**
	 * Turns this shader on.
	 * It will be used until turned off or any other shader is turned on.
	 */
	void use();

	/**
	 * Gets number of a slot bound to a uniform variable.
	 *
	 * @param name A name of a uniform variable.
	 * @return A number of a slot of a uniform variable with given name.
	 */
	GLuint getUniformLocation(const char* name);

	/**
	 * Gets number of a slot bound to an attribute.
	 *
	 * @param name A name of an attribute.
	 * @return A number of a slot of an attribute with given name.
	 */
	GLuint getAttribLocation(const char* name);

	~Shader();

private:
	/**
	 * A handle for a shader program.
	 */
	GLuint shaderProgram;
	/**
	 * A handle for a vertex shader.
	 */
	GLuint vertexShader;
	/**
	 * A handle for a geometry shader.
	 */
	GLuint geometryShader;
	/**
	 * A handle for a fragment shader.
	 */
	GLuint fragmentShader;

	/**
	 * Reads a file with given name as an array of characters.
	 *
	 * @param fileName A name of a file to be read.
	 * @return A contents of a given file in form of a pointer an array of characters.
	 */
	char* readFile(const char* fileName);

	/**
	 * Reads and compiles a shader.
	 *
	 * @param shaderType A type of a shader to process.
	 * @param fileName A name of a file containing shader code.
	 * @return A handle for the processed shader.
	 */
	GLuint loadShader(GLenum shaderType, const char* fileName); //Metoda wczytuje i kompiluje shader, a nast�pnie zwraca jego uchwyt
};


#endif //OPENGL_ARCANOID_SHADER_H
