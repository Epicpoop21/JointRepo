#include "CubeRenderer.h"
#include "Camera.h"

CubeRenderer* CubeRenderer::GetInstance() {
	if (!s_Instance) {
		s_Instance = std::make_unique<CubeRenderer>();
	}
	return s_Instance.get();
}

CubeRenderer::CubeRenderer()
{
	for (int z = -renderDistance; z < renderDistance; z++) {
		for (int x = -renderDistance; x < renderDistance; x++) {
			chunks.push_back(std::make_unique<Chunk>(glm::vec2(x, z)));
			std::cout << "Chunk spawned at: (" << x << ", " << z << ") \n";
		}
	}
}

CubeRenderer::~CubeRenderer()
{

}

void CubeRenderer::Render()
{
	glm::vec2 cameraChunk = Camera::camChunk;
	for (int i = chunks.size() - 1; i >= 0; i--) {
		auto& chunk = chunks[i];
		glm::ivec2 chunkCoords = chunk->chunkCoords;

		if (chunkCoords.y > cameraChunk.y + renderDistance) {
			chunk = std::make_unique<Chunk>(glm::vec2(chunkCoords.x, cameraChunk.y - renderDistance + 1));
			continue;
		}
		if (chunkCoords.y < cameraChunk.y - renderDistance) {
			chunk = std::make_unique<Chunk>(glm::vec2(chunkCoords.x, cameraChunk.y + renderDistance - 1));
			continue;
		}
		if (chunkCoords.x > cameraChunk.x + renderDistance) {
			chunk = std::make_unique<Chunk>(glm::vec2(cameraChunk.x - renderDistance + 1, chunkCoords.y));
			continue;
		}
		if (chunkCoords.x < cameraChunk.x - renderDistance) {
			chunk = std::make_unique<Chunk>(glm::vec2(cameraChunk.x + renderDistance - 1, chunkCoords.y));
			continue;
		}
	}

	for (auto& chunk : chunks) {
		chunk->RenderChunk();
	}
}

int CubeRenderer::GetChunkIndexByWorldCoords(glm::vec3 coords)
{
	for (int i = chunks.size() - 1; i >= 0; i--) {
		glm::vec2 chunkCoords = chunks[i]->chunkCoords;
		if (chunkCoords.x == coords.x && chunks[i] && chunkCoords.y == coords.z) {
			return i;
		}
	}
}

void CubeRenderer::RemoveBlock()
{
	glm::vec3 camDirection = glm::normalize(Camera::cameraFront);
	glm::vec3 blockToBreak = camDirection + Camera::cameraPos;
	int index = GetChunkIndexByWorldCoords(blockToBreak);
	std::cout << "Chunk pos to break is: " << int(blockToBreak.x) % 16 << ", " << int(blockToBreak.z) % 16 << "\n";
	std::cout << "World pos to break is: " << blockToBreak.x << ", " << blockToBreak.y << ", " << blockToBreak.z << "\n";
	std::cout << "Index is: " << index << "\n";
	if (index < 0 || index > chunks.size() - 1) return;
	chunks[index]->RemoveBlock(glm::vec3(int(blockToBreak.x) % 16, blockToBreak.y, int(blockToBreak.z) % 16));
}


