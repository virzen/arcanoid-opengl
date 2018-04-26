#version 330

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

in vec4 vertex;
in vec4 color;
in vec4 normal;

out vec4 c;

void main(void) {
    float d = 1 - (distance(V*M*vertex, vec4(0,0,0,1)) - 3.3)/1.7;

    vec4 mod_vertex = vertex;
	gl_Position=P*V*M*mod_vertex;
	c = vec4(color.xyz*d, color.a);
}


