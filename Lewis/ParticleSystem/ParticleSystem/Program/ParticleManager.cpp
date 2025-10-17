#include "ParticleManager.h"

ParticleManager::ParticleManager(Shader& shader) : particleRadius(10.0f), shader(shader)
{

	for (float y = 20.0f; y < 1080.0f; y += particleRadius * 2 + 30.0f) {
		for (float x = 20.0f; x < 1920.0f; x += particleRadius * 2 + 30.0f) {
			particles.push_back({ glm::vec2(x, y) });
		}
	}

	std::cout << "NUMBER OF PARTICLES IS: " << particles.size() << "\n";
	/*
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

	for (Particle particle : particles) {
		vertexPositions.push_back(particle.coords.x - particleRadius);
		vertexPositions.push_back(particle.coords.y - particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);

		vertexPositions.push_back(particle.coords.x - particleRadius);
		vertexPositions.push_back(particle.coords.y + particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);

		vertexPositions.push_back(particle.coords.x + particleRadius);
		vertexPositions.push_back(particle.coords.y - particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);

		vertexPositions.push_back(particle.coords.x + particleRadius);
		vertexPositions.push_back(particle.coords.y + particleRadius);
		vertexPositions.push_back(particle.coords.x);
		vertexPositions.push_back(particle.coords.y);
	}
	*/

	indices = {
		0, 1, 2,
		1, 2, 3
	};

	vertexPositions.push_back(0.0f - particleRadius);
	vertexPositions.push_back(0.0f - particleRadius);
	vertexPositions.push_back(0.0f);
	vertexPositions.push_back(0.0f);
	
	vertexPositions.push_back(0.0f - particleRadius);
	vertexPositions.push_back(0.0f + particleRadius);
	vertexPositions.push_back(0.0f);
	vertexPositions.push_back(0.0f); 
	
	vertexPositions.push_back(0.0f + particleRadius);
	vertexPositions.push_back(0.0f - particleRadius);
	vertexPositions.push_back(0.0f);
	vertexPositions.push_back(0.0f); 
	
	vertexPositions.push_back(0.0f + particleRadius);
	vertexPositions.push_back(0.0f + particleRadius);
	vertexPositions.push_back(0.0f);
	vertexPositions.push_back(0.0f);

	for (float pos : vertexPositions) {
		std::cout << pos << "\n";
	}

	ib = new IndexBuffer(indices.data(), indices.size() * sizeof(unsigned int));
	vb = new VertexBuffer(vertexPositions.data(), vertexPositions.size() * sizeof(float));
	vbl = new VertexBufferLayout();


	vbl->Push<float>(2);
	vbl->Push<float>(2);
	va->AddBuffer(vbl, vb);
	vb->Unbind();
	std::cout << "vertexPositions.size() = " << vertexPositions.size() << "\n";
	std::cout << "indices.size() = " << indices.size() << "\n";
}

ParticleManager::~ParticleManager()
{
}



void ParticleManager::SetupShader()
{
	shader.Use();
	shader.SetFloat("radius", particleRadius);
}

void ParticleManager::Render()
{
	/*va.Bind();
	ib.Bind();
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0); 
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "OpenGL error: " << err << std::endl;
	}*/
}
