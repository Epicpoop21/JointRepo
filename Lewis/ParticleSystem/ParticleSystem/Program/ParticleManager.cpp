#include "ParticleManager.h"

ParticleManager::ParticleManager(Shader& shader, GameData* gameData) 
	: particleRadius(1.0f), 
	particleSpacing(2.0f), 
	particleBounciness(0.7f), 
	particleInitialVelocity(100.0f), 
	particleRepelDistance(0.0f), 
	mouseRadius(300.0f),
	shader(shader), gameData(gameData)
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float>vel(-particleInitialVelocity, particleInitialVelocity);

	EventHandler* eventHandler = EventHandler::GetInstance();
	eventHandler->GameEventDispatcher.AddListener(GameEvents::MouseIsDown,
		std::bind(&ParticleManager::Click, this, std::placeholders::_1));

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

	float quadVertices[] = {
		-particleRadius, -particleRadius,
		-particleRadius,  particleRadius,
		 particleRadius, -particleRadius,
		 particleRadius,  particleRadius
	};


	VertexArray va;
	va.Bind();
	VertexBuffer quadVBO = VertexBuffer(vertexPositions.data(), vertexPositions.size() * sizeof(float), GL_DYNAMIC_DRAW);
	VertexBuffer instanceVB = VertexBuffer(vertexPositions.data(), vertexPositions.size() * sizeof(float), GL_DYNAMIC_DRAW);
	IndexBuffer ib = IndexBuffer(indices.data(), indices.size() * sizeof(unsigned int));
	VertexBufferLayout vbl;

	vbl.Push<float>(2);
	vbl.Push<float>(3);
	va.AddBuffer(vbl, quadVBO);


	renderObjects = new RenderInfo{ std::move(va), std::move(quadVBO), std::move(instanceVB), std::move(ib), std::move(vbl) };
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

void ParticleManager::Render()
{
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
		//particle.velocity.y = particle.velocity.y - 300.0f * deltaTime;
		particle.coords += particle.velocity * deltaTime;
		if (particle.coords.x + particleRadius > gameData->screenX - particleRepelDistance || particle.coords.x - particleRadius < 0.0f + particleRepelDistance) {
			particle.velocity.x *= -0.9f;
		} 
		while (particle.coords.x + particleRadius > gameData->screenX - particleRepelDistance) {
			particle.coords.x -= 10.0f;
		}
		while (particle.coords.x - particleRadius < 0.0f + particleRepelDistance) {
			particle.coords.x += 10.0f;
		}
		if (particle.coords.y + particleRadius > gameData->screenY - particleRepelDistance || particle.coords.y - particleRadius < 0.0f + particleRepelDistance) {
			particle.velocity.y *= -0.9f;
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
	vertexPositions.erase(vertexPositions.begin(), vertexPositions.end());
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

void ParticleManager::Click(const Event<GameEvents>& gameEvent)
{
	glm::vec2 centre = gameData->mousePos;
	float explosionStrength = 100.0f;
	//std::cout << "X: " << gameData->mousePos.x << " Y: " << gameData->mousePos.y << "\n";
	for (Particle& particle : particles) {
		glm::vec2 toParticle = particle.coords - centre;
		float dist2 = glm::dot(toParticle, toParticle);


		if (dist2 < mouseRadius * mouseRadius) {
			float dist = glm::sqrt(dist2);
			if (dist > 0.0f) {
				glm::vec2 normalised = toParticle / dist;
				float force = (1.0f - dist / mouseRadius) * explosionStrength;
				particle.velocity += normalised * force;
			}
			//std::cout << "X velocity: " << particle.velocity.x << "Y velocity: " << particle.velocity.y << "\n";
		}
	}
	Render();
}

glm::vec2 ParticleManager::GenerateRandomVelocity()
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float>vel(-particleInitialVelocity, particleInitialVelocity);

	return glm::vec2(vel(rng), vel(rng));
}


