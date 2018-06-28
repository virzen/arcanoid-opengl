//Created by dopieralad on 2018/05/02.

#include "brick.h"

unsigned int Brick::VERTEX_COUNT = 36;

static float VERTICES_DATA[] = {
		1.0f, 0.0f, -1.0f, 1.0f,
		-1.0f, 1.15f, -1.0f, 1.0f,
		-1.0f, 0.0f, -1.0f, 1.0f,

		1.0f, 0.0f, -1.0f, 1.0f,
		1.0f, 1.15f, -1.0f, 1.0f,
		-1.0f, 1.15f, -1.0f, 1.0f,

		-1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.15f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		-1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f, 1.15f, 1.0f, 1.0f,
		1.0f, 1.15f, 1.0f, 1.0f,

		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.15f, -1.0f, 1.0f,
		1.0f, 0.0f, -1.0f, 1.0f,

		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.15f, 1.0f, 1.0f,
		1.0f, 1.15f, -1.0f, 1.0f,

		-1.0f, 0.0f, -1.0f, 1.0f,
		-1.0f, 1.15f, 1.0f, 1.0f,
		-1.0f, 0.0f, 1.0f, 1.0f,

		-1.0f, 0.0f, -1.0f, 1.0f,
		-1.0f, 1.15f, -1.0f, 1.0f,
		-1.0f, 1.15f, 1.0f, 1.0f,

		-1.0f, 0.0f, -1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, -1.0f, 1.0f,

		-1.0f, 0.0f, -1.0f, 1.0f,
		-1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,

		-1.0f, 1.15f, 1.0f, 1.0f,
		1.0f, 1.15f, -1.0f, 1.0f,
		1.0f, 1.15f, 1.0f, 1.0f,

		-1.0f, 1.15f, 1.0f, 1.0f,
		-1.0f, 1.15f, -1.0f, 1.0f,
		1.0f, 1.15f, -1.0f, 1.0f,

};
float* Brick::VERTICES = VERTICES_DATA;

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
float* Brick::COLORS = COLORS_DATA;

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
float* Brick::NORMALS = NORMALS_DATA;


Brick::Brick() {
	matrix = glm::mat4(1.0f);
}

unsigned int Brick::getVertexCount() const {
	return VERTEX_COUNT;
}

float* Brick::getVertices() const {
	return VERTICES;
}

float* Brick::getColors() const {
	return COLORS;
}

float* Brick::getNormals() const {
	return NORMALS;
}
