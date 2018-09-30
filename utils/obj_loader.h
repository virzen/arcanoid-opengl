//Created by dopieralad on 2018/07/28.

#ifndef OPENGL_ARCANOID_OBJ_LOADER_H
#define OPENGL_ARCANOID_OBJ_LOADER_H

#include <glm/vec3.hpp>
#include <vector>

bool loadOBJ(
		const char * path,
		std::vector < glm::vec3 > & out_vertices,
		std::vector < glm::vec2 > & out_uvs,
		std::vector < glm::vec3 > & out_normals
);

#endif //OPENGL_ARCANOID_OBJ_LOADER_H
