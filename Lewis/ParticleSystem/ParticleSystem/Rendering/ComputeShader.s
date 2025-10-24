#version 440 core

uniform float deltaTime;
uniform float radius;
uniform vec2 screenDimention;
uniform float repelDistance;

struct Particle {
	vec2 coords;
	vec2 velocity;
};

layout (std430, binding = 0) buffer ParticleBuffer {
	Particle particles[];
};

layout (local_size_x = 256, local_size_y = 1, local_size_z = 1) in;

void main() {
	uint i = gl_GlobalInvocationID.x;
    if (i >= particles.length()) return;	

	particles[i].coords += particles[i].velocity * deltaTime;

	if (particles[i].coords.x + radius > screenDimention.x - repelDistance || particles[i].coords.x - radius < repelDistance) {
		particles[i].velocity.x *= -1.0f;
	}

	if (particles[i].coords.y + radius > screenDimention.y - repelDistance || particles[i].coords.y - radius < repelDistance) {
		particles[i].velocity.y *= -1.0f;
	}
}