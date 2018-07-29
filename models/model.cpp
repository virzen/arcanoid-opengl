//Created by dopieralad on 2018/05/02.

#include <cstdio>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "model.h"
#include "../utils/obj_loader.h"

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
	computeInitialBoundingBox();

	return new BoundingBox(initialBoundingBox->getMinX(), initialBoundingBox->getMinY(),
	                       initialBoundingBox->getMaxX(), initialBoundingBox->getMaxY());
}

void Model::computeInitialBoundingBox() {
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();

	float* vertices = getVertices();
	float* verticesInWorldSpace = new float[getVertexCount()];
	glm::vec4 singleVertex;

	for (int i = 0; i < getVertexCount(); i += 4) {
		singleVertex = matrix * glm::vec4(vertices[i], vertices[i + 1], vertices[i + 2], vertices[i + 3]);
		verticesInWorldSpace[i] = singleVertex[0];
		verticesInWorldSpace[i + 1] = singleVertex[1];
		verticesInWorldSpace[i + 2] = singleVertex[2];
		verticesInWorldSpace[i + 3] = singleVertex[3];
	}

	for (int i = 0; i < getVertexCount(); i += 4) {
		minX = std::min(minX, verticesInWorldSpace[i]);
		minY = std::min(minY, verticesInWorldSpace[i + 1]);

		maxX = std::max(maxX, verticesInWorldSpace[i]);
		maxY = std::max(maxY, verticesInWorldSpace[i + 1]);
	}

	initialBoundingBox = new BoundingBox(minX, minY, maxX, maxY);
}

Model::Model() : initialBoundingBox(nullptr) {}

void Model::rotate(float angle, glm::vec3 axis) {
	matrix = glm::rotate(matrix, angle, axis);
}

void Model::translate(glm::vec3 axis) {
	matrix = glm::translate(matrix, axis);
}

void Model::loadModel(const char* filename) {
	matrix = glm::mat4(1.0f);

	std::vector<glm::vec3> objVertices;
	std::vector<glm::vec2> objUvs;
	std::vector<glm::vec3> objNormals; // Won't be used at the moment.

	loadOBJ(filename, objVertices, objUvs, objNormals);

	setVertexCount(static_cast<unsigned int>(objVertices.size()));
	auto* vertices = (float*) malloc(sizeof(float) * getVertexCount() * 4);
	setVertices(vertices);
	auto* colors = (float*) malloc(sizeof(float) * getVertexCount() * 4);
	setColors(colors);
	auto* normals = (float*) malloc(sizeof(float) * getVertexCount() * 4);
	setNormals(normals);

	unsigned int vertexIndex = 0;
	for (int i = 0; i < objVertices.size(); i++) {
		vertices[vertexIndex] = objVertices[i].x;
		vertices[vertexIndex + 1] = objVertices[i].y;
		vertices[vertexIndex + 2] = objVertices[i].z;
		vertices[vertexIndex + 3] = 1.0f;
		colors[vertexIndex] = 1.0f;
		colors[vertexIndex + 1] = (float) i / getVertexCount();
		colors[vertexIndex + 2] = (float) i / getVertexCount();
		colors[vertexIndex + 3] = 1.0f;
		vertexIndex += 4;
	}
}

unsigned int Model::getVertexCount() const {
	return vertexCount;
}

void Model::setVertexCount(unsigned int vertexCount) {
	Model::vertexCount = vertexCount;
}

float* Model::getVertices() const {
	return vertices;
}

void Model::setVertices(float* vertices) {
	Model::vertices = vertices;
}

float* Model::getColors() const {
	return colors;
}

void Model::setColors(float* colors) {
	Model::colors = colors;
}

float* Model::getNormals() const {
	return normals;
}

void Model::setNormals(float* normals) {
	Model::normals = normals;
}
