//Created by dopieralad on 2018/05/02.

#ifndef OPENGL_ARCANOID_MODEL_H
#define OPENGL_ARCANOID_MODEL_H


#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "boundingBox/boundingBox.h"

/**
 * This is an abstract class representing a 3D model.
 *
 * Apart from delivering information how the model should look like,
 * it also provides the model's state, such as its position, rotation
 * and other game-related attributes: damage, movement direction etc.
 */
class Model {

public:
	unsigned int getVertexCount() const;

	void setVertexCount(unsigned int vertexCount);

	float* getVertices() const;

	void setVertices(float* vertices);

	float* getColors() const;

	void setColors(float* colors);

	float* getNormals() const;

	void setNormals(float* normals);

	/**
	 * Gets model's matrix.
	 *
	 * @return A 4x4 matrix representing this model's position.
	 */
	const glm::mat4 &getMatrix() const;

	/**
	 * Sets a new position matrix for this model.
	 *
	 * @param matrix A new position matrix.
	 */
	void setMatrix(const glm::mat4 &matrix);

	glm::vec4 getCenter();

	BoundingBox* getBoundingBox();

	void rotate(float angle, glm::vec3 axis);

	void translate(glm::vec3 axis);

	void loadModel(const char* filename);

	double getSpeed() const;

	void setSpeed(double speed);

	void accelerate(double acceleration, double direction);

	double getDirection() const;

	void setDirection(double direction);


private:
	/**
	 * A number of vertices shared among all instances of this class.
	 */
	unsigned int vertexCount;
	/**
	 * Model's triangles shared among all instances of this class.
	 */
	float* vertices;
	/**
	 * Triangle's colors shared among all instances of this class.
	 */
	float* colors;
	/**
	 * Triangle's normal vectors shared among all instances of this class.
	 */
	float* normals;
	/**
	 * A 4x4 matrix representing this model's position.
	 */
	glm::mat4 matrix;
	float minX = 0.0f;
	float maxX = 0.0f;
	float minY = 0.0f;
	float maxY = 0.0f;
	/**
	 * Model's speed in units per second.
	 */
	double speed = 0.0f;
	/**
	 * Direction in radians, counter clockwise.
	 * Should never be bigger than 2PI and lower than 0.
	 */
	double direction = 0.0f;
};


#endif //OPENGL_ARCANOID_MODEL_H
