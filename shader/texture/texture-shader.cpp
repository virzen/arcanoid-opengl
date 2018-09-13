//Created by dopieralad on 2018/09/13.

#include <glm/gtc/type_ptr.hpp>
#include "texture-shader.h"

TextureShader::TextureShader() : Shader("shader/texture/vertexShader.vert", nullptr, "shader/texture/fragmentShader.frag") {}

void TextureShader::draw(Model* model, glm::mat4 perspectiveMatrix, glm::mat4 viewMatrix) {
	Shader::draw(model, perspectiveMatrix, viewMatrix);
	
	//Pass all matrices to the shader
	glUniformMatrix4fv(getUniformLocation("perspectiveMatrix"), 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	glUniformMatrix4fv(getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(model->getMatrix()));

	//Enable attributes
	glEnableVertexAttribArray(getAttribLocation("vertexCoordinates"));
	glEnableVertexAttribArray(getAttribLocation("vertexColor"));
	glEnableVertexAttribArray(getAttribLocation("vertexNormal"));

	//Pass attributes to the shader
	glVertexAttribPointer(getAttribLocation("vertexCoordinates"), 4, GL_FLOAT, GL_FALSE, 0, model->getVertices());
	glVertexAttribPointer(getAttribLocation("vertexColor"), 4, GL_FLOAT, GL_FALSE, 0, model->getColors());
	glVertexAttribPointer(getAttribLocation("vertexNormal"), 4, GL_FLOAT, GL_FALSE, 0, model->getNormals());

	//Draw the object
	glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

	//Clean up
	glDisableVertexAttribArray(getAttribLocation("vertexCoordinates"));
	glDisableVertexAttribArray(getAttribLocation("vertexColor"));
	glDisableVertexAttribArray(getAttribLocation("vertexNormal"));
}