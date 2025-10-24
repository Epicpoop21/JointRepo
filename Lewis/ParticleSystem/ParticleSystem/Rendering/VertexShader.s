#version 440 core

layout(location = 0) in vec2 quadPos;

struct Particle {
    vec2 coords;
    vec2 velocity;
};

layout(std430, binding = 0) buffer ParticleBuffer {
    Particle particles[];
};

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float radius;
uniform vec2 screenDimention;

out vec2 vCircleCentre;
out float vSpeed;

void main() {
    uint i = gl_InstanceID;
    Particle p = particles[i];

    vCircleCentre = p.coords;
    vSpeed = length(p.velocity);

    vec4 worldPosition;

    if (radius > 0.5) {
        vec2 worldPos = quadPos + p.coords;
        worldPosition = vec4(worldPos, 0.0, 1.0);
    } else {
        // flip y if necessary
        vec2 flipped = vec2(p.coords.x, screenDimention.y - p.coords.y);
        worldPosition = vec4(flipped, 0.0, 1.0);
        gl_PointSize = max(radius * 2.0, 1.0);
    }

    gl_Position = projection * view * model * worldPosition;
}