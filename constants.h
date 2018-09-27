//Created by dopieralad on 2018/05/01.

#ifndef OPENGL_ARCANOID_CONSTANTS_H
#define OPENGL_ARCANOID_CONSTANTS_H

const float PI = 3.141592653589793f; //PI number approximation

const float CAMERA_SPEED = 2.0f; //Speed of camera's movement in units per second
const double PAD_MAX_SPEED = 50.0f; //Speed of paddle's movement in units per second
const double PAD_ACCELERATION = 100.0f; //Paddle's acceleration in units per square second
const double PAD_REGRESSION = 0.3f; //Paddle's speed regression as a fraction of actual speed
const double PAD_MIN_REGRESSION = 1.0f; //Paddle's minimal speed regression in units
const float BALL_SPEED = 7.0f;
const float BOUNCE_ACCELERATION_FACTOR = 0.5f;


#endif //OPENGL_ARCANOID_CONSTANTS_H
