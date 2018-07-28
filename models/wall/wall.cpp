//Created by dopieralad on 2018/05/02.

#include <glm/ext.hpp>
#include "wall.h"

unsigned int Wall::VERTEX_COUNT = 36;

static float VERTICES_DATA[] = {
		20.0f, 0.0f, -1.0f, 1.0f,
		-20.0f, 1.15f, -1.0f, 1.0f,
		-20.0f, 0.0f, -1.0f, 1.0f,

		20.0f, 0.0f, -1.0f, 1.0f,
		20.0f, 1.15f, -1.0f, 1.0f,
		-20.0f, 1.15f, -1.0f, 1.0f,

		-20.0f, 0.0f, 1.0f, 1.0f,
		20.0f, 1.15f, 1.0f, 1.0f,
		20.0f, 0.0f, 1.0f, 1.0f,

		-20.0f, 0.0f, 1.0f, 1.0f,
		-20.0f, 1.15f, 1.0f, 1.0f,
		20.0f, 1.15f, 1.0f, 1.0f,

		20.0f, 0.0f, 1.0f, 1.0f,
		20.0f, 1.15f, -1.0f, 1.0f,
		20.0f, 0.0f, -1.0f, 1.0f,

		20.0f, 0.0f, 1.0f, 1.0f,
		20.0f, 1.15f, 1.0f, 1.0f,
		20.0f, 1.15f, -1.0f, 1.0f,

		-20.0f, 0.0f, -1.0f, 1.0f,
		-20.0f, 1.15f, 1.0f, 1.0f,
		-20.0f, 0.0f, 1.0f, 1.0f,

		-20.0f, 0.0f, -1.0f, 1.0f,
		-20.0f, 1.15f, -1.0f, 1.0f,
		-20.0f, 1.15f, 1.0f, 1.0f,

		-20.0f, 0.0f, -1.0f, 1.0f,
		20.0f, 0.0f, 1.0f, 1.0f,
		20.0f, 0.0f, -1.0f, 1.0f,

		-20.0f, 0.0f, -1.0f, 1.0f,
		-20.0f, 0.0f, 1.0f, 1.0f,
		20.0f, 0.0f, 1.0f, 1.0f,

		-20.0f, 1.15f, 1.0f, 1.0f,
		20.0f, 1.15f, -1.0f, 1.0f,
		20.0f, 1.15f, 1.0f, 1.0f,

		-20.0f, 1.15f, 1.0f, 1.0f,
		-20.0f, 1.15f, -1.0f, 1.0f,
		20.0f, 1.15f, -1.0f, 1.0f,

};
float* Wall::VERTICES = VERTICES_DATA;

static float COLORS_DATA[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,

		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
};
float* Wall::COLORS = COLORS_DATA;

static float NORMALS_DATA[] = {
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,

		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,

		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,

		1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f,

		-1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f,

		-1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f, 0.0f,

		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,

		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
};
float* Wall::NORMALS = NORMALS_DATA;


Wall::Wall() {
	matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(0.0f, 9.0f, 0.0f));
}

unsigned int Wall::getVertexCount() const {
	return VERTEX_COUNT;
}

float* Wall::getVertices() const {
	return VERTICES;
}

float* Wall::getColors() const {
	return COLORS;
}

float* Wall::getNormals() const {
	return NORMALS;
}
