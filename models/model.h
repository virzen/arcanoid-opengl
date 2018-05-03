//Created by dopieralad on 2018/05/02.

#ifndef OPENGL_ARCANOID_MODEL_H
#define OPENGL_ARCANOID_MODEL_H


#include <glm/detail/type_mat.hpp>
#include <glm/detail/type_mat4x4.hpp>

/**
 * This is an abstract class representing a 3D model.
 *
 * Apart from delivering information how the model should look like,
 * it also provides the model's state, such as its position, rotation
 * and other game-related attributes: damage, movement direction etc.
 */
class Model {

public:
	/**
	 * Gets number of vertices forming this model.
	 *
	 * @return A positive number of vertices.
	 */
	virtual unsigned int getVertexCount() const = 0;

	/**
	 * Gets Euler coordinates of all triangles forming this model.
	 *
	 * @return An array of triangle coordinates.
	 */
	virtual float* getVertices() const = 0;

	/**
	 * Gets colors for each triangle forming this model.
	 *
	 * @return An array of triangle colors.
	 */
	virtual float* getColors() const = 0;

	/**
	 * Gets normal vectors for each triangle forming this model.
	 *
	 * @return An array of normal vectors.
	 */
	virtual float* getNormals() const = 0;

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

protected:
	/**
	 * A 4x4 matrix representing this model's position.
	 */
	glm::mat4 matrix;
};


#endif //OPENGL_ARCANOID_MODEL_H
