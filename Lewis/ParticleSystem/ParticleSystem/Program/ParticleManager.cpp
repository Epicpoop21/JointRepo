#include "ParticleManager.h"

ParticleManager::ParticleManager(Shader& shader, GameData* gameData)
	: particleRadius(1.0f),
	particleSpacing(3.0f),
	particleBounciness(0.9f),
	particleInitialVelocity(100.0f),
	particleRepelDistance(5.0f),
	mouseRadius(1000.0f),
	explosionStrength(4000.0f),
	shader(shader), gameData(gameData)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float>vel(-particleInitialVelocity, particleInitialVelocity);

	minDistanceBetweenParticles = particleRadius * 2.0f + particleRepelDistance;
	cellSize = particleRadius * 2.5f;

	float vX;
	float vY;
	for (float y = particleRadius; y < gameData->screenY; y += particleRadius * 2 + particleSpacing) {
		for (float x = particleRadius; x < gameData->screenX; x += particleRadius * 2 + particleSpacing) {
			vX = vel(rng);
			vY = vel(rng);
			particles.push_back({ glm::vec2(x, y), glm::vec2(vX, vY) });
		}
	}

	std::cout << "NUMBER OF PARTICLES IS: " << particles.size() << "\n";
	
	indices = {
		0, 1, 2,
		1, 2, 3
	};

	/*for (Particle& particle : particles) {
		std::cout << particle.velocity.x << "    " << particle.velocity.y << "\n";
	}*/

	int quadSize = 0;
	float quadVertices[8];
	if (particleRadius > 0.5f) {
		float temp[] = {
			-particleRadius, -particleRadius,
			-particleRadius,  particleRadius,
			 particleRadius, -particleRadius,
			 particleRadius,  particleRadius
		};
		memcpy(quadVertices, temp, sizeof(temp));
		quadSize = sizeof(temp);
	}
	else {
		float temp[] = {
			particleRadius, particleRadius
		};
		memcpy(quadVertices, temp, sizeof(temp));
		quadSize = sizeof(temp);
	} 

	VertexArray va;
	va.Bind();
	VertexBufferLayout vbl1;
	VertexBufferLayout vbl2;
	ShaderStorageBuffer ssb = ShaderStorageBuffer(particles.data(), particles.size() * sizeof(Particle));
	IndexBuffer ib = IndexBuffer(indices.data(), indices.size() * sizeof(unsigned int));

	VertexBuffer quadVBO = VertexBuffer(quadVertices, sizeof(quadVertices), GL_STATIC_DRAW);
	vbl1.Push<float>(2);
	va.AddBuffer(vbl1, quadVBO);

	renderObjects = new RenderInfo{ std::move(va), std::move(quadVBO), std::move(ib), std::move(vbl1), std::move(vbl2), std::move(ssb)};
}

ParticleManager::~ParticleManager()
{
	delete renderObjects;
}

void ParticleManager::Setup()
{
	shader.UseGraphics();
	shader.SetFloat("radius", particleRadius);
	shader.SetFloat("initialVelocity", particleInitialVelocity);
	shader.SetVec2f("screenDimention", gameData->screenX, gameData->screenY);

	shader.UseCompute();
	shader.SetFloat("explosionStrength", explosionStrength);
	shader.SetFloat("mouseRadius", mouseRadius);
	shader.SetFloat("particleInitialVelocity", particleInitialVelocity);
	shader.SetFloat("particleRepelDistance", particleRepelDistance);
	shader.SetFloat("particleRadius", particleRadius);
}

void ParticleManager::Render(float deltaTime)
{
	shader.UseCompute();
	renderObjects->ssb.Bind();

	shader.SetFloat("deltaTime", deltaTime);
	shader.SetVec2f("screenDimention", gameData->screenX, gameData->screenY);
	shader.SetFloat("repelDistance", particleRepelDistance);
	shader.SetFloat("radius", particleRadius);
	shader.SetBool("clicking", gameData->mouseDown);
	shader.SetVec2f("mousePos", gameData->mousePos.x, gameData->mousePos.y);

	unsigned int numGroups = (particles.size() + 256 - 1) / 256;
	glDispatchCompute(numGroups, 1, 1);
	glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT | GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT);

	shader.UseGraphics();
	renderObjects->va.Bind();
	renderObjects->ib.Bind();

	glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, particles.size());
}

void ParticleManager::Vibrate(float deltaTime)
{
	/*for (Particle& particle : particles) {
		//particle.velocity.y = particle.velocity.y - 300.0f * deltaTime;
		particle.coords += particle.velocity * deltaTime;
		if (particle.coords.x + particleRadius > gameData->screenX - particleRepelDistance || particle.coords.x - particleRadius < 0.0f + particleRepelDistance) {
			particle.velocity.x *= -1.0f;
		} 
		if (particle.coords.y + particleRadius > gameData->screenY - particleRepelDistance || particle.coords.y - particleRadius < 0.0f + particleRepelDistance) {
			particle.velocity.y *= -1.0f;
		}
		while (particle.coords.x + particleRadius > gameData->screenX - particleRepelDistance) {
			particle.coords.x -= 10.0f;
		}
		while (particle.coords.x - particleRadius < 0.0f + particleRepelDistance) {
			particle.coords.x += 10.0f;
		}

		while (particle.coords.y + particleRadius > gameData->screenY - particleRepelDistance) {
			particle.coords.y -= 10.0f;
		}
		while (particle.coords.y - particleRadius < 0.0f + particleRepelDistance) {
			particle.coords.y += 10.0f;
		}
		if (glm::length(particle.velocity) > particleInitialVelocity * 10) {
			particle.velocity = GenerateRandomVelocity();
		}  
	}
	instanceData.erase(instanceData.begin(), instanceData.end());*/
}

void ParticleManager::CheckCollisions()
{
	BuildSpatialHash();
	for (int i = 0; i < particles.size(); i++) {
		glm::ivec2 cell = GetCellCoordinates(particles[i].coords, cellSize);

		for (auto& offset : neighbouringOffsets) {
			glm::ivec2 neighbourCell = cell + glm::ivec2(offset[0], offset[1]);
			int64_t neighbourHash = HashCell(neighbourCell.x, neighbourCell.y);

			auto it = grid.find(neighbourHash);
			if (it == grid.end()) continue;

			for (int j : it->second) {
				if (i == j) continue;

				glm::vec2 difference = particles[j].coords - particles[i].coords;
				float dist2 = glm::dot(difference, difference);

				if (dist2 < minDistanceBetweenParticles * minDistanceBetweenParticles && dist2 > 0.0f) {
					float dist = std::sqrt(dist2);
					glm::vec2 normal = difference / dist;

					float overlap = 0.5f * (minDistanceBetweenParticles - dist);
					particles[i].coords -= normal * overlap;
					particles[j].coords += normal * overlap;

					glm::vec2 reflectVel = particles[j].velocity - particles[i].velocity;
					float velAlongNormal = glm::dot(reflectVel, normal);

					if (velAlongNormal < 0.0f) {
						float impulse = -(1.0f + particleBounciness) * velAlongNormal / 1.9f;

						particles[i].velocity -= impulse * normal;
						particles[j].velocity += impulse * normal;
					}
				}
			}
		}
	}
}

inline int64_t ParticleManager::HashCell(int x, int y)
{
	return (static_cast<int64_t>(x) << 32) | static_cast<uint32_t>(y);
}

inline glm::ivec2 ParticleManager::GetCellCoordinates(const glm::vec2& pos, float cellSize)
{
	return glm::ivec2(
		static_cast<int>(std::floor(pos.x / cellSize)),
		static_cast<int>(std::floor(pos.y / cellSize))
	);
}

void ParticleManager::BuildSpatialHash()
{
	grid.clear();
	for (int i = 0; i < particles.size(); i++) {
		glm::ivec2 cell = GetCellCoordinates(particles[i].coords, cellSize);
		int64_t hash = HashCell(cell.x, cell.y);
		grid[hash].push_back(i);
	}
}

glm::vec2 ParticleManager::GenerateRandomVelocity()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float>vel(-particleInitialVelocity, particleInitialVelocity);

	return glm::vec2(vel(rng), vel(rng));
}


