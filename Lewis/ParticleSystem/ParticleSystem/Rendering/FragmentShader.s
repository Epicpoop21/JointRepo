#version 440 core

in vec2 vCircleCentre;
in float vSpeed;

uniform float radius;
uniform float initialVelocity;

out vec4 FragColor;

void main() {
	vec2 fragPos = gl_FragCoord.xy;
	float dist = length(fragPos - vCircleCentre);
	if (dist > radius) discard;

	float r, b;

	r = sqrt(vSpeed * vSpeed);
	b = sqrt(vSpeed * vSpeed);
	r = r / initialVelocity;
	b = (1 / b) * (initialVelocity / 4);

	FragColor = vec4(r, 0.0f, b, 1.0f);
}