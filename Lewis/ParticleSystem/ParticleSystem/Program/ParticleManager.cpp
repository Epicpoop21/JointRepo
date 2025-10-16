#include "ParticleManager.h"

ParticleManager::ParticleManager(Shader& shader) : particleRadius(10.0f), shader(shader)
{
	for (float y = 20.0f; y < 1080.0f; y += particleRadius * 2 + 30.0f) {
		for (float x = 20.0f; x < 1920.0f; x += particleRadius * 2 + 30.0f) {
			if (particles.size() < 1001) {
				particles.push_back({ glm::vec2(x, y) });
			}
		}
	}

	std::cout << "NUMBER OF PARTICLES IS: " << particles.size() << "\n";
}

ParticleManager::~ParticleManager()
{
}



void ParticleManager::SetupShader()
{
	shader.Use();
	shader.SetInt("numberOfCircles", particles.size());
	shader.SetFloat("radius", particleRadius);
}

void ParticleManager::Render()
{
	shader.SetVec2fv("circleCentres", particles.size(), glm::value_ptr(particles[0].coords));
}
