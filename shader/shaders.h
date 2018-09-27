//Created by dopieralad on 2018/09/13.

#ifndef OPENGL_ARCANOID_SHADERS_H
#define OPENGL_ARCANOID_SHADERS_H


#include "shader.h"

class Shaders {

public:
	static Shader* colorShader();

	static Shader* brickShader();

	static Shader* ballShader();

private:
	static Shader* colorShaderInstance;
	static Shader* brickShaderInstance;
	static Shader* ballShaderInstance;
};


#endif //OPENGL_ARCANOID_SHADERS_H
