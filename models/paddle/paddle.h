//Created by dopieralad on 2018/05/02.

#ifndef OPENGL_ARCANOID_PAD_H
#define OPENGL_ARCANOID_PAD_H


#include "../model.h"

/**
 * This is a class representing an Arkanoid paddle.
 */
class Paddle : public Model {

public:
	/**
	 * Paddle's default constructor.
	 */
	Paddle();

	double getSpeed() const;

	void setSpeed(double speed);

private:
	double speed = 0.0f;
};


#endif //OPENGL_ARCANOID_PAD_H
