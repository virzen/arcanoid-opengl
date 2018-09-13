//Created by dopieralad on 2018/09/13.

#include "shaders.h"
#include "color/color-shader.h"
#include "texture/texture-shader.h"

Shader* Shaders::colorShaderInstance = nullptr;
Shader* Shaders::textureShaderInstance = nullptr;

Shader* Shaders::colorShader() {
	if (colorShaderInstance == nullptr) {
		colorShaderInstance = new ColorShader();
	}

	return colorShaderInstance;
}

Shader* Shaders::textureShader() {
	if (textureShaderInstance == nullptr) {
		textureShaderInstance = new TextureShader();
	}

	return textureShaderInstance;
}
