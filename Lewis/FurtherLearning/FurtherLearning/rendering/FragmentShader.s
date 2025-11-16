#version 440 core

out vec4 FragColor;
in vec2 texCoords;

uniform sampler2D textureImage;

void main() {
	FragColor = texture(textureImage, texCoords);
}