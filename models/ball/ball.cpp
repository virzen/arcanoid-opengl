//Created by dopieralad on 2018/05/02.

#include "ball.h"
#include <vector>
#include <cstdio>
#include "../../utils/obj_loader.h"

unsigned int Ball::VERTEX_COUNT = 36;

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
float* Ball::VERTICES = VERTICES_DATA;

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
float* Ball::COLORS = COLORS_DATA;

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
float* Ball::NORMALS = NORMALS_DATA;

Ball::Ball() {
	matrix = glm::mat4(1.0f);

	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals; // Won't be used at the moment.

	loadOBJ("./models/ball/ball.obj", vertices, uvs, normals);

	printf("Vertices: %ld\n", vertices.size());
	printf("UVs: %ld\n", uvs.size());
	printf("Normals: %ld\n", normals.size());
}

unsigned int Ball::getVertexCount() const {
	return VERTEX_COUNT;
}

float* Ball::getVertices() const {
	return VERTICES;
}

float* Ball::getColors() const {
	return COLORS;
}

float* Ball::getNormals() const {
	return NORMALS;
}
