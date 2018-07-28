//Created by dopieralad on 2018/05/02.

#include "ball.h"
#include <vector>
#include <cstdio>
#include <glm/ext.hpp>
#include "../../utils/obj_loader.h"

unsigned int Ball::VERTEX_COUNT;
float* Ball::VERTICES;
float* Ball::COLORS;
float* Ball::NORMALS;

Ball::Ball() {
	matrix = glm::mat4(1.0f);
	matrix = glm::translate(matrix, glm::vec3(0.0f, 0.0f, 0.0f));

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.

	loadOBJ("./models/ball/ball.obj", vertices, uvs, normals);

	VERTEX_COUNT = static_cast<unsigned int>(vertices.size());
	VERTICES = (float*) malloc(sizeof(float) * VERTEX_COUNT * 4);
	COLORS = (float*) malloc(sizeof(float) * VERTEX_COUNT * 4);
	NORMALS = (float*) malloc(sizeof(float) * VERTEX_COUNT * 4);

	for (int i = 0; i < VERTEX_COUNT; i += 4) {
		VERTICES[i] = vertices[i].x;
		VERTICES[i + 1] = vertices[i].y;
		VERTICES[i + 2] = vertices[i].z;
		VERTICES[i + 3] = 1.0f;
		COLORS[i] = 0;
		COLORS[i + 1] = (float) i / VERTEX_COUNT;
		COLORS[i + 2] = (float) i / VERTEX_COUNT;
		COLORS[i + 3] = 1.0f;
	}
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
