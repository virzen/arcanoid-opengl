//Created by dopieralad on 2018/09/13.

#ifndef OPENGL_ARCANOID_METALSHADER_H
#define OPENGL_ARCANOID_METALSHADER_H

#include "../shader.h"

class MetalShader : public Shader {

public:
	explicit MetalShader(const char* metalFile);

	void draw(Model* model, glm::mat4 perspectiveMatrix, glm::mat4 viewMatrix) override;

private:
	GLuint texture;
};


#endif //OPENGL_ARCANOID_METALSHADER_H
