//Created by dopieralad on 2018/07/28.

#include <cstdio>
#include <string>
#include "bounce.h"

enum Side {
	top = 0, right, bottom, left
};

std::string enumNames[] = {
		"top",
		"right",
		"bottom",
		"left",
};

float calculateSlope(Model* object) {
	BoundingBox* box = object->getBoundingBox();

	float slope = (box->getMaxY() - box->getMinY()) / (box->getMaxX() - box->getMinX());

	return slope;
}

Side calculateSide(Ball* ball, Model* object) {
	glm::vec4 ballCenter = ball->getCenter();
	glm::vec4 objectCenter = object->getCenter();
	float objectSlope = calculateSlope(object);

	printf("Slope: %f\n", objectSlope);

	float positiveBallCenterFactor = ballCenter.y - ballCenter.x * objectSlope;
	float positiveObjectCenterFactor = objectCenter.y - objectCenter.x * objectSlope;

	bool hasGreaterPositiveFactor = positiveBallCenterFactor > positiveObjectCenterFactor;

	float negativeBallCenterFactor = ballCenter.y - ballCenter.x * -1.0f * objectSlope;
	float negativeObjectCenterFactor = objectCenter.y - objectCenter.x * -1.0f * objectSlope;

	bool hasGreaterNegativeFactor = negativeBallCenterFactor > negativeObjectCenterFactor;

	printf("ball coords: (%f, %f)\nobject coords: (%f, %f)\n", ballCenter.x, ballCenter.y, objectCenter.x, objectCenter.y);
	printf("positive: %f %f, negative: %f %f\n", positiveBallCenterFactor, positiveObjectCenterFactor, negativeBallCenterFactor, negativeObjectCenterFactor);

	if (hasGreaterPositiveFactor && hasGreaterNegativeFactor) {
		return top;
	}

	if (!hasGreaterPositiveFactor && hasGreaterNegativeFactor) {
		return right;
	}

	if (!hasGreaterPositiveFactor && !hasGreaterNegativeFactor) {
		return bottom;
	}

	return left;
}

// TODO: move to Game?
void bounce(Ball* ball, Model* object, glm::vec2* ballCoordsModifiers) {
	Side side = calculateSide(ball, object);

	printf("Collision from %s side\n", enumNames[side].c_str());

	if (side == top || side == bottom) {
		ballCoordsModifiers->y = -1 * ballCoordsModifiers->y;
	} else {
		ballCoordsModifiers->x = -1 * ballCoordsModifiers->x;
	}

	printf("\n");
};
