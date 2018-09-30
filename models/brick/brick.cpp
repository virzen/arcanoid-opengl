//Created by dopieralad on 2018/05/02.

#include "brick.h"
#include "../../shader/shaders.h"

Brick::Brick() {
	loadModel("./models/brick/brick.obj");
	setShader(Shaders::brickShader());
}
