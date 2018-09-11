//Created by dopieralad on 2018/05/02.

#include <cstdio>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "model.h"
#include "../utils/obj_loader.h"
#include "../constants.h"

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
	center.z = 0.0f; // Z axis is not taken into account and is 0 by default

	return center;
}

BoundingBox* Model::getBoundingBox() {
	auto leftBottomVertex = matrix * glm::vec4(minX, minY, 0.0f, 1.0f);
	auto rightTopVertex = matrix * glm::vec4(maxX, maxY, 0.0f, 1.0f);

	return new BoundingBox(leftBottomVertex.x, leftBottomVertex.y, rightTopVertex.x, rightTopVertex.y);
}

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
	std::vector<glm::vec3> objNormals;

	loadOBJ(filename, objVertices, objUvs, objNormals);

	setVertexCount(static_cast<unsigned int>(objVertices.size()));
	auto* vertices = (float*) malloc(sizeof(float) * getVertexCount() * 4);
	setVertices(vertices);
	auto* colors = (float*) malloc(sizeof(float) * getVertexCount() * 4);
	setColors(colors);
	auto* normals = (float*) malloc(sizeof(float) * getVertexCount() * 4);
	setNormals(normals);


	for (int i = 0, vertexIndex = 0; i < objVertices.size(); i++) {
		auto vertex = objVertices[i];
		auto normal = objNormals[i];
		vertices[vertexIndex] = vertex.x;
		vertices[vertexIndex + 1] = vertex.y;
		vertices[vertexIndex + 2] = vertex.z;
		vertices[vertexIndex + 3] = 1.0f;
		colors[vertexIndex] = 1.0f;
		colors[vertexIndex + 1] = (float) i / getVertexCount();
		colors[vertexIndex + 2] = (float) i / getVertexCount();
		colors[vertexIndex + 3] = 1.0f;
		normals[vertexIndex] = normal.x;
		normals[vertexIndex + 1] = normal.y;
		normals[vertexIndex + 2] = normal.z;
		normals[vertexIndex + 3] = 0.0f;
		vertexIndex += 4;

		if (vertex.x < minX) {
			minX = vertex.x;
		}

		if (vertex.x > maxX) {
			maxX = vertex.x;
		}

		if (vertex.y < minY) {
			minY = vertex.y;
		}

		if (vertex.y > maxY) {
			maxY = vertex.y;
		}
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

double Model::getSpeedX() const {
	return speedX;
}

void Model::setSpeedX(double speedX) {
	Model::speedX = speedX;
}

double Model::getSpeedY() const {
	return speedY;
}

void Model::setSpeedY(double speedY) {
	Model::speedY = speedY;
};
