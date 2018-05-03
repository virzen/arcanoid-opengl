//Created by dopieralad on 2018/05/02.

#include "model.h"

const glm::mat4 &Model::getMatrix() const {
	return matrix;
}

void Model::setMatrix(const glm::mat4 &matrix) {
	Model::matrix = matrix;
}
