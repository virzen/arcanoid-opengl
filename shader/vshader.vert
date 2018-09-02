#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 vertex;
in vec4 color;
in vec4 normal;

out vec4 c;

void main(void) {

    vec4 mod_vertex = vertex;
	gl_Position = P * V * M * mod_vertex;
	c = color;
}


