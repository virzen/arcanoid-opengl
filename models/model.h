//Created by dopieralad on 2018/05/02.

#ifndef OPENGL_ARCANOID_MODEL_H
#define OPENGL_ARCANOID_MODEL_H


#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>
#include "boundingBox/boundingBox.h"

class Shader;

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

	float* getUvs() const;

	void setUvs(float* uvs);

	float* getNormals() const;

	void setNormals(float* normals);

	float* getColors() const;

	void setColors(float* colors);

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

	double getSpeedX() const;

	void setSpeedX(double speedX);

	double getSpeedY() const;

	void setSpeedY(double speedY);

	Shader* getShader() const;

	void setShader(Shader* shader);

	float getColorModifier();

	int getHitpoints();

	void addHitpoint();

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
	 * Triangle's texture coordinates.
	 */
	float* uvs;
	/**
	 * Triangle's normal vectors shared among all instances of this class.
	 */
	float* normals;
	/**
	 * Triangle's colors shared among all instances of this class.
	 */
	float* colors;
	/**
	 * A 4x4 matrix representing this model's position.
	 */
	glm::mat4 matrix;
	float minX = 0.0f;
	float maxX = 0.0f;
	float minY = 0.0f;
	float maxY = 0.0f;
	double speedX = 0.0f;
	double speedY = 0.0f;

	Shader* shader;

	int hitpoints = 0;
};


#endif //OPENGL_ARCANOID_MODEL_H
