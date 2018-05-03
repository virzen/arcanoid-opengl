//Created by dopieralad on 2018/05/02.

#include "paddle.h"

unsigned int Paddle::VERTEX_COUNT = 36;

static float VERTICES_DATA[] = {
		1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,


		-1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,

		1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f, 1.0f,

		-1.0f, -1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f, 1.0f,

		-1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,

		-1.0f, 1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, -1.0f, 1.0f,

};
float* Paddle::VERTICES = VERTICES_DATA;

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
float* Paddle::COLORS = COLORS_DATA;

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
float* Paddle::NORMALS = NORMALS_DATA;


Paddle::Paddle() {
	matrix = glm::mat4(1.0f);
}

unsigned int Paddle::getVertexCount() const {
	return VERTEX_COUNT;
}

float* Paddle::getVertices() const {
	return VERTICES;
}

float* Paddle::getColors() const {
	return COLORS;
}

float* Paddle::getNormals() const {
	return NORMALS;
}
