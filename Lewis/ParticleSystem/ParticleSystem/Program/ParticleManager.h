#pragma once
#include "../Rendering/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <random>
#include <unordered_map>

struct Particle {
	glm::vec2 coords = glm::vec2(0.0f, 0.0f);
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
};

class ParticleManager
{
public:
	ParticleManager(Shader& shader);
	~ParticleManager();

	void Setup();
	void Render(float deltaTime);
	void Vibrate(float deltaTime);
	void CheckCollisions();
private:

	inline int64_t HashCell(int x, int y);
	inline glm::ivec2 GetCellCoordinates(const glm::vec2& pos, float cellSize);
	void BuildSpatialHash();

public:

private:
	float particleSpacing;
	float particleBounciness;
	float particleInitialVelocity;
	float particleRepelDistance;

	Shader& shader;
	float particleRadius;
	float minDistanceBetweenParticles;
	float cellSize;
	std::vector<Particle> particles;
	std::unordered_map<int64_t, std::vector<int>> grid;
	std::vector<float> vertexPositions;
	std::vector<unsigned int> indices;
	RenderInfo* renderObjects = nullptr;

	const int neighbouringOffsets[9][2] = {
		{-1, -1}, {0, -1}, {1, -1},
		{-1,  0}, {0,  0}, {1,  0},
		{-1,  1}, {0,  1}, {1,  1}
	};
};

