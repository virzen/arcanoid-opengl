//Created by dopieralad on 2018/07/28.

#include <cstdio>
#include "../models/ball/ball.h"
#include "../models/brick/brick.h"
#include "../models/boundingBox/boundingBox.h"

// TODO: move to Game?
bool doesCollide(Ball* ball,
                 Model* object) {
	glm::vec4 ballCenter = ball->getCenter();
	glm::vec4 objectCenter = object->getCenter();
	BoundingBox* ballBoundingBox = ball->getBoundingBox();
	BoundingBox* objectBoundingBox = object->getBoundingBox();

	bool collisionX = ballBoundingBox->getMaxX() >= objectBoundingBox->getMinX() && objectBoundingBox->getMaxX() >= ballBoundingBox->getMinX();
	bool collisionY = ballBoundingBox->getMaxY() >= objectBoundingBox->getMinY() && objectBoundingBox->getMaxY() >= ballBoundingBox->getMinY();

	return collisionX && collisionY;
}