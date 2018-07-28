//Created by dopieralad on 2018/07/28.

#include <glm/vec2.hpp>
#include "boundingBox.h"

glm::vec2 BoundingBox::getUpperLeft() {
	return glm::vec2();
}

glm::vec2 BoundingBox::getLowerRight() {
	return glm::vec2();
}

float BoundingBox::getMaxX() const {
	return maxX;
}

float BoundingBox::getMinX() const {
	return minX;
}

float BoundingBox::getMaxY() const {
	return maxY;
}

float BoundingBox::getMinY() const {
	return minY;
}

BoundingBox::BoundingBox(float minX, float minY, float maxX, float maxY) : maxX(maxX), minX(minX), maxY(maxY), minY(minY) {}
