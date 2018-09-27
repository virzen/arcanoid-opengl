#version 330

// Uniform variables
uniform sampler2D textureMap;

// Interpolated input variables
in vec4 lightVectors[2];
in vec4 normalVector;
in vec4 viewerVector;
in vec2 textureCoordinate;

out vec4 pixelColor; // Fragment shader output variable

vec4 colorForLight(vec4 lightVector) {
    int lightFocus = 1; // Phong exponent
    vec4 outputColor = texture(textureMap, textureCoordinate);

	vec4 normalizedLightVector = normalize(lightVector);
	vec4 normalizedNormalVector = normalize(normalVector);
	vec4 normalizedViewerVector = normalize(viewerVector);

    vec4 ambientMaterialColor = outputColor;
    vec4 ambientLightColor = vec4(0.2, 0.2, 0.2, 1);
    vec4 ambientColor = ambientMaterialColor * ambientLightColor;

    vec4 diffuseMaterialColor = outputColor;
    vec4 diffuseLightColor = vec4(1, 1, 1, 1);
    float nl = max(dot(normalizedNormalVector, normalizedLightVector), 0);
    vec4 diffuseColor = diffuseMaterialColor * diffuseLightColor * vec4(nl, nl, nl, 1);

    vec4 specularMaterialColor = 4 * outputColor;
	vec4 specularLightColor = vec4(1, 1, 1, 1);
	vec4 reflectionVector = reflect(-normalizedLightVector, normalizedNormalVector);
	float reflectionFactor = pow(max(0, dot(reflectionVector, normalizedViewerVector)), lightFocus);
	vec4 specularColor = specularMaterialColor * specularLightColor * reflectionFactor;

    return ambientColor + diffuseColor + specularColor;
}

void main(void) {
    pixelColor = 0.5 * colorForLight(lightVectors[0]) + 0.5 * colorForLight(lightVectors[1]);
}
