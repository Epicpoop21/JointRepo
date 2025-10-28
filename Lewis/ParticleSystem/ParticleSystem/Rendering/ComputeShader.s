#version 440 core

uniform float deltaTime;
uniform float radius;
uniform vec2 screenDimention;
uniform float repelDistance;
uniform float particleInitialVelocity;
uniform float particleRadius;
uniform float particleRepelDistance;

uniform vec2 mousePos;
uniform float mouseRadius;
uniform float explosionStrength;
uniform bool clicking;

struct Particle {
	vec2 coords;
	vec2 velocity;
};

layout (std430, binding = 0) buffer ParticleBuffer {
	Particle particles[];
};

layout (local_size_x = 256, local_size_y = 1, local_size_z = 1) in;


float rand(uint seed)
{
    seed = (seed ^ 61u) ^ (seed >> 16u);
    seed *= 9u;
    seed = seed ^ (seed >> 4u);
    seed *= 0x27d4eb2du;
    seed = seed ^ (seed >> 15u);
    return float(seed & 0xFFFFFFFu) / float(0xFFFFFFFu); // returns 0.0 - 1.0
}


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

	while (particles[i].coords.y + particleRadius > screenDimention.y - particleRepelDistance) {
		particles[i].coords.y -= 10.0f;
	}
	while (particles[i].coords.y - particleRadius < 0.0f + particleRepelDistance) {
		particles[i].coords.y += 10.0f;
	}

	while (particles[i].coords.x + particleRadius > screenDimention.x - particleRepelDistance) {
		particles[i].coords.x -= 10.0f;
	}
	while (particles[i].coords.x - particleRadius < 0.0f + particleRepelDistance) {
		particles[i].coords.x += 10.0f;
	}

	if (length(particles[i].velocity) > particleInitialVelocity * 10.0f)
    {
        // Reset to a random velocity
        float angle = rand(i) * 6.2831853; // 0 to 2*PI
        float speed = rand(i + 1u) * particleInitialVelocity;
        particles[i].velocity = vec2(cos(angle), sin(angle)) * speed;
    }

	if (clicking) {
		vec2 toParticle = mousePos - particles[i].coords;
		float dist2 = dot(toParticle, toParticle);

		if (dist2 < pow(mouseRadius, 2)) {
			float dist = sqrt(dist2);
			if (dist > 0.0f) {
				vec2 normalised = toParticle / dist;
				float force = (1.0f - dist / mouseRadius) * explosionStrength;
				particles[i].velocity += normalised * force;
			}
		}
	}
}

float rand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}