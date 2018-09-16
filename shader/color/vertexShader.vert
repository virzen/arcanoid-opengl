#version 330

// Uniform variables
uniform mat4 perspectiveMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;

// Attributes
in vec4 vertexCoordinates; // Vertex coordinates in model space
in vec4 vertexColor;  // Vertex color
in vec4 vertexNormal; // Vertex normal vector in model space

// Interpolated output variables
out vec4 outputColor;
out vec4 lightVectors[2];
out vec4 normalVector;
out vec4 viewerVector;

void main(void) {
    // Light positions in world space
    vec4 lightPosition1 = vec4(0, 20, 25, 1);
    vec4 lightPosition2 = vec4(0, 20, 500, 1);

   	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vertexCoordinates;
    outputColor = vertexColor;
    lightVectors[0] = normalize(viewMatrix * lightPosition1 - viewMatrix * modelMatrix * vertexCoordinates);
    lightVectors[1] = normalize(viewMatrix * lightPosition2 - viewMatrix * modelMatrix * vertexCoordinates);
    normalVector = normalize(viewMatrix * modelMatrix * vertexNormal);
	viewerVector = normalize(vec4(0, 0, 0, 1) - viewMatrix * modelMatrix * vertexCoordinates);
}
