#version 440 core

in vec2 localPos;
uniform float radius;
uniform vec3 colour;

out vec4 FragColor;

void main() {
	if (length(localPos) > radius) {
		FragColor = vec4(1.0f, 0.2f, 0.4f, 1.0f);
		//discard;
	}

	FragColor = vec4(colour, 1.0f);
}