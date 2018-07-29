//Created by dopieralad on 2018/05/02.

#include <cstdio>
#include <algorithm>
#include "model.h"

const glm::mat4 &Model::getMatrix() const {
	return matrix;
}

void Model::setMatrix(const glm::mat4 &matrix) {
	Model::matrix = matrix;
}

glm::vec4 Model::getCenter() {
	BoundingBox* boundingBox = getBoundingBox();
	glm::vec4 center = glm::vec4(1.0f);

	center.x = boundingBox->getMaxX() - (boundingBox->getMaxX() - boundingBox->getMinX()) / 2;
	center.y = boundingBox->getMaxY() - (boundingBox->getMaxY() - boundingBox->getMinY()) / 2;
	//Z axis is not taken into account

	return center;
}

BoundingBox* Model::getBoundingBox() {
	glm::vec4 center = Model::matrix[3];

	if (initialBoundingBox == nullptr) {
		computeInitialBoundingBox();
	}

	return new BoundingBox(center.x + initialBoundingBox->getMinX(), center.y + initialBoundingBox->getMinY(),
	                       center.x + initialBoundingBox->getMaxX(), center.y + initialBoundingBox->getMaxY());
}

void Model::computeInitialBoundingBox() {
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();

	float* vertices = getVertices();
	for (int i = 0; i < getVertexCount(); i += 4) {
		minX = std::min(minX, vertices[i]);
		minY = std::min(minY, vertices[i + 1]);

		maxX = std::max(maxX, vertices[i]);
		maxY = std::max(maxY, vertices[i + 1]);
	}

	initialBoundingBox = new BoundingBox(minX, minY, maxX, maxY);
}

Model::Model() : initialBoundingBox(nullptr) {}
