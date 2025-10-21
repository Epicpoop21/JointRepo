#version 440 core

layout (location = 0) in vec2 aQuadPos;
layout (location = 1) in vec3 aInstanceData;

out vec2 circleCentre;
out float speed;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float radius;
void main() {
	vec4 worldPosition;
	circleCentre = aInstanceData.xy;
	speed = aInstanceData.z;

	if (radius > 0.5) {
		vec2 worldPos = aQuadPos + circleCentre;
		worldPosition = vec4(worldPos, 0.0f, 1.0f);
	} else {
		worldPosition = vec4(circleCentre, 0.0f, 1.0f);
        gl_PointSize = max(radius * 2.0, 1.0);
	}
	gl_Position = projection * view * model * worldPosition;
}