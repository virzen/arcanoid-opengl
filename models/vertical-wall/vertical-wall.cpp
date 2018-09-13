//Created by dopieralad on 2018/05/02.

#include "vertical-wall.h"
#include "../../shader/shaders.h"

VerticalWall::VerticalWall() {
	loadModel("./models/vertical-wall/vertical-wall.obj");
	setShader(Shaders::colorShader());
}