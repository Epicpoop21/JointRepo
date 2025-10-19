#version 440 core

layout (location = 0) in vec2 aQuadPos;
layout (location = 1) in vec3 aInstanceData;

out vec2 circleCentre;
out float speed;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
	circleCentre = aInstanceData.xy;
	speed = aInstanceData.z;

	vec2 worldPos = aQuadPos + circleCentre;
	gl_Position = projection * view * model * vec4(worldPos, 0.0f, 1.0f);
}