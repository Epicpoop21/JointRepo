#include "CubeRenderer.h"
#include "Camera.h"
#include <cmath>

int CubeRenderer::renderDistance = 4;
std::vector<std::unique_ptr<Chunk>> CubeRenderer::chunks{};
std::unique_ptr<CubeRenderer> CubeRenderer::s_Instance = nullptr;
Texture CubeRenderer::textureGrid = Texture(nullptr);
Shader* CubeRenderer::shader = nullptr;

CubeRenderer* CubeRenderer::GetInstance() {
	if (!s_Instance) {
		s_Instance = std::make_unique<CubeRenderer>();
	}
	return s_Instance.get();
}

CubeRenderer::CubeRenderer()
{
	textureGrid.LaterCompilation("res/textures/TextureGrid.png");
	for (int z = -renderDistance; z < renderDistance; z++) {
		for (int x = -renderDistance; x < renderDistance; x++) {
			chunks.push_back(std::make_unique<Chunk>(glm::vec2(x, z), textureGrid));
			std::cout << "Chunk spawned at: (" << x << ", " << z << ") \n";
		}
	}
	std::cout << "Number of chunks is: " << chunks.size() << "\n";
}

CubeRenderer::~CubeRenderer()
{

}

void CubeRenderer::AddShader(Shader* shader)
{
	CubeRenderer::shader = shader;
}

void CubeRenderer::Render()
{
	glm::vec2 cameraChunk = Camera::camChunk;
	for (int i = chunks.size() - 1; i >= 0; i--) {
		auto& chunk = chunks[i];
		glm::ivec2 chunkCoords = chunk->chunkCoords;
		
		if (chunkCoords.y > cameraChunk.y + renderDistance) {
			chunk = std::make_unique<Chunk>(glm::vec2(chunkCoords.x, cameraChunk.y - renderDistance + 1), textureGrid);
			continue;
		}
		if (chunkCoords.y < cameraChunk.y - renderDistance) {
			chunk = std::make_unique<Chunk>(glm::vec2(chunkCoords.x, cameraChunk.y + renderDistance - 1), textureGrid);
			continue;
		}
		if (chunkCoords.x > cameraChunk.x + renderDistance) {
			chunk = std::make_unique<Chunk>(glm::vec2(cameraChunk.x - renderDistance + 1, chunkCoords.y), textureGrid);
			continue;
		}
		if (chunkCoords.x < cameraChunk.x - renderDistance) {
			chunk = std::make_unique<Chunk>(glm::vec2(cameraChunk.x + renderDistance - 1, chunkCoords.y), textureGrid);
			continue;
		} 
	}
	shader->Use();
	shader->SetMat4f("view", Camera::view);
	shader->SetMat4f("projection", Camera::projection);
	for (auto& chunk : chunks) {
		chunk->RenderChunk();
	}
}

int CubeRenderer::GetChunkIndexByWorldCoords(glm::vec3 coords)
{
	glm::vec2 chunkToFind = WorldCoordsToChunk(coords);
	for (int i = chunks.size() - 1; i >= 0; i--) {
		glm::vec2 iChunkCoords = chunks[i]->chunkCoords;
		//std::cout << "Converted normal coords are: (" << chunkToFind.x << ", " << chunkToFind.y << ")\n";
		if (iChunkCoords.x == chunkToFind.x && iChunkCoords.y == chunkToFind.y) {
			return i;
		}
	}
	return -1;
}

void CubeRenderer::RemoveBlock()
{
	glm::vec3 camDirection = glm::normalize(Camera::cameraFront);
	for (int i = 1; i < 5; i++) {
		glm::vec3 blockToBreak = glm::vec3(((float)i * camDirection) + Camera::cameraPos);
		if (blockToBreak.y < 0) continue;
		int index = GetChunkIndexByWorldCoords(blockToBreak);
		glm::vec2 localChunkPos = WorldCoordToLocalChunkCoord(blockToBreak, chunks[index]->chunkCoords);
		/*std::cout << "\n \n ==========================================\n";
		std::cout << i << "\n";
		std::cout << "Chunk pos to break is: " << localChunkPos.x << ", " << localChunkPos.y << "\n";
		std::cout << "World pos to break is: " << blockToBreak.x << ", " << blockToBreak.y << ", " << blockToBreak.z << "\n";
		std::cout << "Camera pos is: " << Camera::cameraPos.x << ", " << Camera::cameraPos.y << ", " << Camera::cameraPos.z << "\n";
		std::cout << camDirection.length() << "\n"; */
		if (index < 0 || index > chunks.size() - 1) return;
		glm::vec3* passedCoordinates = new glm::vec3(localChunkPos.x, blockToBreak.y, localChunkPos.y);
		if (chunks[index]->RemoveBlock(passedCoordinates)) {
			return;
		}
	}
}

glm::vec2 CubeRenderer::WorldCoordsToChunk(glm::vec3 coords)
{
	glm::vec2 convertedCoords = glm::vec2(int(coords.x) / 16, int(coords.z) / 16);
	if (coords.x < 0) {
		convertedCoords.x--;
	} if (coords.z < 0) {
		convertedCoords.y--;
	}
	return convertedCoords;
}

glm::vec2 CubeRenderer::WorldCoordToLocalChunkCoord(glm::vec3 worldCoords, glm::vec2 chunkCoords)
{
	glm::vec2 resultingChunkCoord = glm::vec2(0.0f, 0.0f);

	if (worldCoords.x > 0) {
		resultingChunkCoord.x = (int)std::floor(worldCoords.x) - (16 * chunkCoords.x);
	}
	else {
		resultingChunkCoord.x = (int)std::floor(worldCoords.x) - (16 * chunkCoords.x);
	}
	if (worldCoords.z > 0) {
		resultingChunkCoord.y = (int)std::floor(worldCoords.z) - (16 * chunkCoords.y);
	}
	else {
		resultingChunkCoord.y = (int)std::floor(worldCoords.z) - (16 * chunkCoords.y);
	}
	return resultingChunkCoord;
}

