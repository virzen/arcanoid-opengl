//Created by dopieralad on 2018/07/28.

#ifndef OPENGL_ARCANOID_BOUNDINGBOX_H
#define OPENGL_ARCANOID_BOUNDINGBOX_H


#include <glm/vec2.hpp>

class BoundingBox {
public:
	BoundingBox(float minX, float minY, float maxX, float maxY);

	glm::vec2 getUpperLeft();

	glm::vec2 getLowerRight();

	float getMaxX() const;

	float getMinX() const;

	float getMaxY() const;

	float getMinY() const;

private:
	float maxX;
	float minX;
	float maxY;
	float minY;
};


#endif //OPENGL_ARCANOID_BOUNDINGBOX_H
