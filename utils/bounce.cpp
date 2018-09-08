//Created by dopieralad on 2018/07/28.

#include <cstdio>
#include <string>
#include "bounce.h"
#include "../constants.h"

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

void reposition(Ball* ball, Model* object, Side side) {
	auto ballBoundingBox = ball->getBoundingBox();
	auto objectBoundingBox = object->getBoundingBox();

	if (side == top) {
		auto yOffset = objectBoundingBox->getMaxY() - ballBoundingBox->getMinY();
		printf("Offset: %020f", yOffset);
		ball->translate(glm::vec3(0.0f, yOffset, 0.0f));
	} else if (side == bottom) {
		auto yOffset = objectBoundingBox->getMinY() - ballBoundingBox->getMaxY();
		printf("Offset: %020f", yOffset);
		ball->translate(glm::vec3(0.0f, yOffset, 0.0f));
	} else if (side == left) {
		auto xOffset = objectBoundingBox->getMinX() - ballBoundingBox->getMaxX();
		printf("Offset: %020f", xOffset);
		ball->translate(glm::vec3(xOffset, 0.0f, 0.0f));
	} else if (side == right) {
		auto xOffset = objectBoundingBox->getMaxX() - ballBoundingBox->getMinX();
		printf("Offset: %020f", xOffset);
		ball->translate(glm::vec3(xOffset, 0.0f, 0.0f));
	}
}

void accelerateFromCollision(Ball* ball, Model* object, Side side) {
	if (side == top || side == bottom) {
		ball->setSpeedX(ball->getSpeedX() + object->getSpeedX() * BOUNCE_ACCELERATION_FACTOR);
	}

	//TODO Handle side acceleration
}

// TODO: move to Game?
void bounce(Ball* ball, Model* object) {
	Side side = calculateSide(ball, object);

	printf("Collision from %s side\n", enumNames[side].c_str());
	reposition(ball, object, side);

	if (side == top || side == bottom) {
		ball->setSpeedY(-ball->getSpeedY());
	} else {
		ball->setSpeedX(-ball->getSpeedX());
	}

	accelerateFromCollision(ball, object, side);
}
