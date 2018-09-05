//Created by dopieralad on 2018/05/02.

#include <cstdio>
#include "paddle.h"

Paddle::Paddle() {
	loadModel("./models/paddle/paddle.obj");
}

double Paddle::getSpeed() const {
	return speed;
}

void Paddle::setSpeed(double speed) {
	Paddle::speed = speed;
}


