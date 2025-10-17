#version 440 core

in vec2 circleCentre;
uniform float radius;
uniform vec3 colour;

out vec4 FragColor;

void main() {
	if (pow(gl_FragCoord.x - circleCentre.x, 2) + pow(gl_FragCoord.y - circleCentre.y, 2) > pow(radius, 2)) {
		FragColor = vec4(1.0f, 0.2f, 0.4f, 1.0f);
		//discard;
	}

	FragColor = vec4(colour, 1.0f);
}