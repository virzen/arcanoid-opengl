//Created by dopieralad on 2018/05/02.

#include "ball.h"
#include "../../utils/obj_loader.h"
#include "../../shader/shaders.h"

Ball::Ball() {
	loadModel("./models/ball/ball.obj");
	setShader(Shaders::colorShader());

	this->translate(glm::vec3(0.0f, 1.0f, 0.0f));
}