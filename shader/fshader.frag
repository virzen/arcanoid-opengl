#version 330

// Interpolated input variables
in vec4 outputColor;
in vec4 lightVector;
in vec4 normalVector;
in vec4 viewerVector;

out vec4 pixelColor; // Fragment shader output variable

void main(void) {
    vec4 ka = vec4(0, 0, 0, 0);
    vec4 kd = outputColor;
	vec4 ks = vec4(1, 1, 1, 0);

    vec4 la = vec4(0, 0, 0, 0);
    vec4 ld = vec4(1, 1, 1, 1);
	vec4 ls = vec4(1, 1, 1, 0);

	vec4 ml = normalize(lightVector);
	vec4 mn = normalize(normalVector);
	vec4 mv = normalize(viewerVector);

	vec4 r = reflect(-ml, mn);

    float nl = max(dot(mn, ml), 0);
	float rv = pow(max(0, dot(r, mv)), 50);

    pixelColor = ka * la + kd * ld * vec4(nl, nl, nl, 1) + ks * ls * rv;
}
