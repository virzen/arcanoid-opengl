#ifndef OPENGL_ARCANOID_BRICK_H
#define OPENGL_ARCANOID_BRICK_H


#include "../model.h"

/**
 * This is a class representing an Arkanoid brick.
 */
class Brick : public Model {
private:
	int hitpoints = 0;

public:
	Brick();

	int getHitpoints();

	void addHitpoint();
};


#endif //OPENGL_ARCANOID_BRICK_H
