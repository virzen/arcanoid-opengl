#version 330

// Interpolated input variables
in vec4 outputColor;
in vec4 lightVector;
in vec4 normalVector;
in vec4 viewerVector;

out vec4 pixelColor; // Fragment shader output variable

void main(void) {
    int lightFocus = 50; // Phong exponent
	vec4 normalizedLightVector = normalize(lightVector);
	vec4 normalizedNormalVector = normalize(normalVector);
	vec4 normalizedViewerVector = normalize(viewerVector);

    vec4 ambientMaterialColor = vec4(0, 0, 0, 0);
    vec4 ambientLightColor = vec4(0, 0, 0, 0);
    vec4 ambientColor = ambientMaterialColor * ambientLightColor;

    vec4 diffuseMaterialColor = outputColor;
    vec4 diffuseLightColor = vec4(1, 1, 1, 1);
    float nl = max(dot(normalizedNormalVector, normalizedLightVector), 0);
    vec4 diffuseColor = diffuseMaterialColor * diffuseLightColor * vec4(nl, nl, nl, 1);

    vec4 specularMaterialColor = vec4(1, 1, 1, 0);
	vec4 specularLightColor = vec4(1, 1, 1, 0);
	vec4 reflectionVector = reflect(-normalizedLightVector, normalizedNormalVector);
	float reflectionFactor = pow(max(0, dot(reflectionVector, normalizedViewerVector)), lightFocus);
	vec4 specularColor = specularMaterialColor * specularLightColor * reflectionFactor;

    pixelColor = ambientColor + diffuseColor + specularColor;
}
