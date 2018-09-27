//Created by dopieralad on 2018/09/13.

#include "shaders.h"
#include "color/color-shader.h"
#include "texture/texture-shader.h"

Shader* Shaders::colorShaderInstance = nullptr;
Shader* Shaders::brickShaderInstance = nullptr;
Shader* Shaders::ballShaderInstance = nullptr;
Shader* Shaders::wallShaderInstance = nullptr;

Shader* Shaders::colorShader() {
	if (colorShaderInstance == nullptr) {
		colorShaderInstance = new ColorShader();
	}

	return colorShaderInstance;
}

Shader* Shaders::brickShader() {
	if (brickShaderInstance == nullptr) {
		brickShaderInstance = new TextureShader("textures/brick.png");
	}

	return brickShaderInstance;
}

Shader* Shaders::ballShader() {
	if (ballShaderInstance == nullptr) {
		ballShaderInstance = new TextureShader("textures/ball.png");
	}

	return ballShaderInstance;
}

Shader* Shaders::wallShader() {
	if (wallShaderInstance == nullptr) {
		wallShaderInstance = new TextureShader("textures/wall.png");
	}

	return wallShaderInstance;
}
