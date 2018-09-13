//Created by dopieralad on 2018/09/13.

#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "texture-shader.h"
#include "../../lib/lodepng/lodepng.h"

TextureShader::TextureShader(const char* textureFile) : Shader("shader/texture/vertexShader.vert", nullptr, "shader/texture/fragmentShader.frag") {
	std::vector<unsigned char> image;
	unsigned width, height; // Image dimensions

	// Read the image
	lodepng::decode(image, width, height, textureFile);

	glGenTextures(1, &texture); // Initialize one handle
	glBindTexture(GL_TEXTURE_2D, texture); // Activate the handle

	// Read image to graphics card memory using activated handle
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

	// Configure active texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}

void TextureShader::draw(Model* model, glm::mat4 perspectiveMatrix, glm::mat4 viewMatrix) {
	Shader::draw(model, perspectiveMatrix, viewMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

	//Pass all matrices to the shader
	glUniformMatrix4fv(getUniformLocation("perspectiveMatrix"), 1, GL_FALSE, glm::value_ptr(perspectiveMatrix));
	glUniformMatrix4fv(getUniformLocation("viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(model->getMatrix()));
	glUniform1i(getUniformLocation("textureMap"), 0);

	//Enable attributes
	glEnableVertexAttribArray(getAttribLocation("vertexCoordinates"));
	glEnableVertexAttribArray(getAttribLocation("vertexNormal"));
	glEnableVertexAttribArray(getAttribLocation("textureCoordinates"));

	//Pass attributes to the shader
	glVertexAttribPointer(getAttribLocation("vertexCoordinates"), 4, GL_FLOAT, GL_FALSE, 0, model->getVertices());
	glVertexAttribPointer(getAttribLocation("vertexNormal"), 4, GL_FLOAT, GL_FALSE, 0, model->getNormals());
	glVertexAttribPointer(getAttribLocation("textureCoordinates"), 2, GL_FLOAT, GL_FALSE, 0, model->getUvs());

	//Draw the object
	glDrawArrays(GL_TRIANGLES, 0, model->getVertexCount());

	//Clean up
	glDisableVertexAttribArray(getAttribLocation("vertexCoordinates"));
	glDisableVertexAttribArray(getAttribLocation("vertexNormal"));
	glDisableVertexAttribArray(getAttribLocation("textureCoordinates"));
}