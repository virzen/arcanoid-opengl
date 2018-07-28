//Created by dopieralad on 2018/07/28.

#ifndef OPENGL_ARCANOID_BOUNCE_H
#define OPENGL_ARCANOID_BOUNCE_H


#include <glm/vec2.hpp>
#include "../models/model.h"
#include "../models/ball/ball.h"

void bounce(Ball* pBall, Model* model, glm::vec2* ballCoordsModifiers);


#endif //OPENGL_ARCANOID_BOUNCE_H
