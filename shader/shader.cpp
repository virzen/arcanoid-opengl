//Created by dopieralad on 2018/04/26.

#include <cstdio>
#include "shader.h"

Shader::Shader(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile) {
	//Load vertex shader
	printf("Loading vertex shader...\n");
	vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderFile);

	//Load geometry shader
	if (geometryShaderFile != nullptr) {
		printf("Loading geometry shader...\n");
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryShaderFile);
	} else {
		geometryShader = 0;
	}

	//Load fragment shader
	printf("Loading fragment shader...\n");
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderFile);

	//Generate handle for the shader program
	shaderProgram = glCreateProgram();

	//Attach shaders to the program and link it
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	if (geometryShaderFile != nullptr) {
		glAttachShader(shaderProgram, geometryShader);
	}
	glLinkProgram(shaderProgram);

	//Get error log and display it
	int infologLength = 0;
	int charsWritten = 0;
	char* infoLog;

	glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1) {
		infoLog = new char[infologLength];
		glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		delete[]infoLog;
	}

	printf("Shader program created\n");
}

void Shader::use() {
	glUseProgram(shaderProgram);
}

GLint Shader::getUniformLocation(const char* variableName) {
	return glGetUniformLocation(shaderProgram, variableName);
}

GLint Shader::getAttribLocation(const char* variableName) {
	return glGetAttribLocation(shaderProgram, variableName);
}

Shader::~Shader() {
	//Detach shaders
	glDetachShader(shaderProgram, vertexShader);
	if (geometryShader != 0) {
		glDetachShader(shaderProgram, geometryShader);
	}
	glDetachShader(shaderProgram, fragmentShader);

	//Delete shaders
	glDeleteShader(vertexShader);
	if (geometryShader != 0) {
		glDeleteShader(geometryShader);
	}
	glDeleteShader(fragmentShader);

	//Delete shader program
	glDeleteProgram(shaderProgram);
}

char* Shader::readFile(const char* fileName) {
	int filesize;
	FILE* plik;
	char* result;

	plik = fopen(fileName, "rb");
	fseek(plik, 0, SEEK_END);
	filesize = ftell(plik);
	fseek(plik, 0, SEEK_SET);
	result = new char[filesize + 1];
	fread(result, 1, filesize, plik);
	result[filesize] = 0;
	fclose(plik);

	return result;
}

GLuint Shader::loadShader(GLenum shaderType, const char* fileName) {
	//Generate shader handle
	GLuint shader = glCreateShader(shaderType);
	//Read shader source code
	const GLchar* shaderSource = readFile(fileName);
	//Link shader source with the handle
	glShaderSource(shader, 1, &shaderSource, nullptr);
	//Compile shader source code
	glCompileShader(shader);
	//Remove shader source code from memory
	delete[]shaderSource;

	//Get error log and display it
	int infologLength = 0;
	int charsWritten = 0;
	char* infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1) {
		infoLog = new char[infologLength];
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		delete[]infoLog;
	}

	//Return generated shader's handles
	return shader;
}