//Created by dopieralad on 2018/05/02.

#include <cstdio>
#include "paddle.h"
#include "../../shader/shaders.h"

Paddle::Paddle() {
	loadModel("./models/paddle/paddle.obj");
	setShader(Shaders::paddleShader());
}
