#ifndef OPENGL_ARCANOID_BALL_H
#define OPENGL_ARCANOID_BALL_H


#include "../model.h"

/**
 * This is a class representing an Arkanoid paddle.
 */
class Ball : public Model {

public:
	/**
	 * Ball's default constructor.
	 */
	Ball();

	unsigned int getVertexCount() const override;

	float* getVertices() const override;

	float* getColors() const override;

	float* getNormals() const override;

protected:
	/**
	 * A number of vertices shared among all instances of this class.
	 */
	static unsigned int VERTEX_COUNT;
	/**
	 * Model's triangles shared among all instances of this class.
	 */
	static float* VERTICES;
	/**
	 * Triangle's colors shared among all instances of this class.
	 */
	static float* COLORS;
	/**
	 * Triangle's normal vectors shared among all instances of this class.
	 */
	static float* NORMALS;
};


#endif //OPENGL_ARCANOID_BALL_H
