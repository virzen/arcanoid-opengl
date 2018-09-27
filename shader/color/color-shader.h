//Created by dopieralad on 2018/09/13.

#ifndef OPENGL_ARCANOID_COLORSHADER_H
#define OPENGL_ARCANOID_COLORSHADER_H

#include "../shader.h"

class ColorShader : public Shader {

public:
	ColorShader();

	void draw(Model* model, glm::mat4 perspectiveMatrix, glm::mat4 viewMatrix) override;
};


#endif //OPENGL_ARCANOID_COLORSHADER_H
