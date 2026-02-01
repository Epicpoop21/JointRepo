#version 460 core

out vec4 FragColor;
in vec3 outCol;

void main() {
	FragColor = vec4(outCol, 0.0f);
}