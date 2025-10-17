#pragma once
#include "../Rendering/Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Particle {
	glm::vec2 coords = glm::vec2(0.0f, 0.0f);
	glm::vec2 velocity = glm::vec2(0.0f, 0.0f);
};

class ParticleManager
{
public:
	ParticleManager(Shader& shader);
	~ParticleManager();

	void SetupShader();
	void Render();
private:

public:

private:
	Shader& shader;
	float particleRadius;
	std::vector<Particle> particles;
	std::vector<float> vertexPositions;
	std::vector<unsigned int> indices;

	VertexArray* va;
	VertexBuffer* vb;
	IndexBuffer* ib;
	VertexBufferLayout* vbl;
};

