#version 440 core

in vec2 circleCentre;
in float speed;
uniform float radius;
uniform vec3 colour;
uniform float initialVelocity;

out vec4 FragColor;

void main() {
	if (pow(gl_FragCoord.x - circleCentre.x, 2) + pow(gl_FragCoord.y - circleCentre.y, 2) > pow(radius, 2)) {
		discard;
	}

	float r, b;

	r = sqrt(speed * speed);
	b = sqrt(speed * speed);
	r = r / initialVelocity;
	b = (1 / b) * (initialVelocity / 6);

	FragColor = vec4(r, 0.0f, b, 1.0f);
}