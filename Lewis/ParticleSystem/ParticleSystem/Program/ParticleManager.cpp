#include "ParticleManager.h"

ParticleManager::ParticleManager(Shader& shader) : particleRadius(15.0f), particleSpacing(10.0f), particleBounciness(1.0f), particleInitialVelocity(100.0f), particleRepelDistance(2.0f), shader(shader)
{
	minDistanceBetweenParticles = particleRadius * 2.0f + particleRepelDistance;
	cellSize = particleRadius * 2.5f;
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float>vel(-particleInitialVelocity, particleInitialVelocity);

	float vX;
	float vY;
	for (float y = particleRadius; y < 1080.0f; y += particleRadius * 2 + particleSpacing) {
		for (float x = particleRadius; x < 1920.0f; x += particleRadius * 2 + particleSpacing) {
			vX = vel(rng);
			vY = vel(rng);
			particles.push_back({ glm::vec2(x, y), glm::vec2(vX, vY) });
		}
	}

	std::cout << "NUMBER OF PARTICLES IS: " << particles.size() << "\n";
	
	int c = 0;
	for (int i = 0; i < particles.size(); i++) {
		indices.push_back(0 + c);
		indices.push_back(1 + c);
		indices.push_back(2 + c);
		indices.push_back(1 + c);
		indices.push_back(2 + c);
		indices.push_back(3 + c);
		c += 4;
	}

	for (Particle& particle : particles) {
		vertexPositions.push_back(particle.coords.x - particleRadius);
		vertexPositions.push_back(particle.coords.y - particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
		//std::cout << glm::length(particle.velocity) << "\n";
		vertexPositions.push_back(glm::length(particle.velocity));

		vertexPositions.push_back(particle.coords.x - particleRadius);
		vertexPositions.push_back(particle.coords.y + particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
		vertexPositions.push_back(glm::length(particle.velocity));

		vertexPositions.push_back(particle.coords.x + particleRadius);
		vertexPositions.push_back(particle.coords.y - particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
		vertexPositions.push_back(glm::length(particle.velocity));

		vertexPositions.push_back(particle.coords.x + particleRadius);
		vertexPositions.push_back(particle.coords.y + particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
		vertexPositions.push_back(glm::length(particle.velocity));
	}

	/*for (Particle& particle : particles) {
		std::cout << particle.velocity.x << "    " << particle.velocity.y << "\n";
	}*/

	VertexArray va;
	IndexBuffer ib = IndexBuffer(indices.data(), indices.size() * sizeof(unsigned int));
	VertexBuffer vb = VertexBuffer(vertexPositions.data(), vertexPositions.size() * sizeof(float), GL_DYNAMIC_DRAW);
	VertexBufferLayout vbl;

	vbl.Push<float>(2);
	vbl.Push<float>(3);
	va.AddBuffer(vbl, vb);


	renderObjects = new RenderInfo{ std::move(va), std::move(vb), std::move(ib), std::move(vbl) };
}

ParticleManager::~ParticleManager()
{
	delete renderObjects;
}



void ParticleManager::Setup()
{
	shader.Use();
	shader.SetFloat("radius", particleRadius);
	shader.SetFloat("initialVelocity", particleInitialVelocity);
}

void ParticleManager::Render(float deltaTime)
{
	renderObjects->va.Bind();
	renderObjects->ib.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); 
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << std::endl;
	}
}

void ParticleManager::Vibrate(float deltaTime)
{
	for (Particle& particle : particles) {
		//particle.velocity.y = particle.velocity.y - 498.0f * deltaTime;
		particle.coords += particle.velocity * deltaTime;
		if (particle.coords.x + particleRadius > 1920.0f - particleRepelDistance || particle.coords.x - particleRadius < 0.0f + particleRepelDistance) {
			particle.velocity.x *= -1.0f;
		} 
		if (particle.coords.y + particleRadius > 1080.0f - particleRepelDistance || particle.coords.y - particleRadius < 0.0f + particleRepelDistance) {
			particle.velocity.y *= -1.0f;
		}
	}
	vertexPositions.erase(vertexPositions.begin(), vertexPositions.end());
	for (Particle& particle : particles) {
		vertexPositions.push_back(particle.coords.x - particleRadius);
		vertexPositions.push_back(particle.coords.y - particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
		vertexPositions.push_back(glm::length(particle.velocity));

		vertexPositions.push_back(particle.coords.x - particleRadius);
		vertexPositions.push_back(particle.coords.y + particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
		vertexPositions.push_back(glm::length(particle.velocity));

		vertexPositions.push_back(particle.coords.x + particleRadius);
		vertexPositions.push_back(particle.coords.y - particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
		vertexPositions.push_back(glm::length(particle.velocity));

		vertexPositions.push_back(particle.coords.x + particleRadius);
		vertexPositions.push_back(particle.coords.y + particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
		vertexPositions.push_back(glm::length(particle.velocity));
	}
	renderObjects->vb.UpdateData(vertexPositions.data(), vertexPositions.size() * sizeof(float), GL_DYNAMIC_DRAW);
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
						float impulse = -(1.0f + particleBounciness) * velAlongNormal / 2.0f;

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

