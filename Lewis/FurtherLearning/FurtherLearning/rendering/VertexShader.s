#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;
layout (location = 2) in vec3 aOffset;

uniform mat4 view;
uniform mat4 projection;

out vec3 col;

void main() {
	vec3 worldPos = aPos + aOffset;
	gl_Position = projection * view * vec4(worldPos, 1.0f);
	col = aCol;
}