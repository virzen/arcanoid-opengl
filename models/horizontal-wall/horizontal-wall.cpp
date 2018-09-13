//Created by dopieralad on 2018/05/02.

#include "horizontal-wall.h"
#include "../../shader/shaders.h"

HorizontalWall::HorizontalWall() {
	loadModel("./models/horizontal-wall/horizontal-wall.obj");
	setShader(Shaders::colorShader());
}