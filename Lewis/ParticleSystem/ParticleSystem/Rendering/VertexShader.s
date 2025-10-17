#version 440 core

layout (location = 0) in vec2 aQuadPos;
layout (location = 1) in vec2 aCircleCentre;

out vec2 localPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	vec2 worldPos = aQuadPos + aCircleCentre;
	localPos = aQuadPos;
	gl_Position = projection * view * model * vec4(worldPos, 0.0f, 1.0f);
}