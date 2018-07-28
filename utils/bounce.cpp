//Created by dopieralad on 2018/07/28.

#include "bounce.h"

// TODO: move to Game?
void bounce(Ball* ball, Model* object, glm::vec2* ballCoordsModifiers) {
	glm::vec4 ballCenter = ball->getCenter();
	BoundingBox* objectBox = object->getBoundingBox();

	bool isUnder = ballCenter.y <= objectBox->getMinY() && ballCenter.x >= objectBox->getMinX() && ballCenter.x <= objectBox->getMaxX();
	bool isAbove = ballCenter.y >= objectBox->getMaxY() && ballCenter.x >= objectBox->getMinX() && ballCenter.x <= objectBox->getMaxX();
	bool isOnTheLeft = ballCenter.x <= objectBox->getMinX() && ballCenter.y >= objectBox->getMinY() && ballCenter.y <= objectBox->getMaxY();
	bool isOnTheRight = ballCenter.x >= objectBox->getMaxX() && ballCenter.y >= objectBox->getMinY() && ballCenter.y <= objectBox->getMaxY();

	if (isUnder || isAbove) {
		ballCoordsModifiers->y = -1.0f * ballCoordsModifiers->y;
	} else if (isOnTheLeft || isOnTheRight) {
		ballCoordsModifiers->x = -1.0f * ballCoordsModifiers->x;
	}
};
