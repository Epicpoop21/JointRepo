#include "Chunk.h"
#include <cmath> 

float Chunk::textureTileSize = (1.0f / 16.0f);
unsigned int Chunk::faceNumber = 0;

Chunk::Chunk(glm::vec2 origin, Texture& textureGrid) : vb(nullptr, 0), ib(nullptr, 0), textureGrid(textureGrid)
{
	this->chunkCoords = origin;
	int y = 0;
	for (int z = 0; z < 16; z++) {
		for (int x = 0; x < 16; x++) {
			blocks[0][z][x] = Block(glm::vec3(x, 0, z), BEDROCK);

			int worldX = origin.x * 16 + x;
			int worldZ = origin.y * 16 + z;

			int heightX = glm::floor(((glm::cos(worldX * 0.2f) * 5.0f) + 8));
			int heightZ = glm::floor(((glm::cos(worldZ * 0.2f) * 5.0f) + 8));

			int totalHeight = heightX + heightZ;
			for (y = 1; y < totalHeight - 2; y++) {
				blocks[y][z][x] = Block(glm::vec3(x, y, z), STONE);
			}
			blocks[totalHeight - 2][z][x] = Block(glm::vec3(x, totalHeight - 2, z), DIRT);
			blocks[totalHeight - 1][z][x] = Block(glm::vec3(x, totalHeight - 1, z), GRASS);
		}
	}
	int totalHeight = 20;
	for (int n = totalHeight; n < totalHeight + 8; n++) {
		blocks[n][0][0] = Block(glm::vec3(0, n, 0), OAKLOG);
	} 
	blocks[totalHeight + 8][0][0] = Block(glm::vec3(0, totalHeight + 8, 0), LEAF);
	vbl.Push<float>(3);	
	vbl.Push<float>(2);

	RebuildMeshes();
}

Chunk::~Chunk()
{
}

void Chunk::RebuildMeshes()
{
	faceNumber = 0;
	vertexInfo.erase(vertexInfo.begin(), vertexInfo.end());
	indexValues.erase(indexValues.begin(), indexValues.end());

	for (int y = 0; y < CHUNK_Y; y++) {
		for (int z = 0; z < CHUNK_Z; z++) {
			for (int x = 0; x < CHUNK_X; x++) {
				Block& evaluatedBlock = blocks[y][z][x];
				if (evaluatedBlock.type == AIR) continue;

				bool topIsAir = (y + 1 >= CHUNK_Y) ? true : (blocks[y + 1][z][x].type == AIR);
				bool bottomIsAir = (y - 1 < 0) ? true : (blocks[y - 1][z][x].type == AIR);
				bool frontIsAir = (z + 1 >= CHUNK_Z) ? true : (blocks[y][z + 1][x].type == AIR);
				bool backIsAir = (z - 1 < 0) ? true : (blocks[y][z - 1][x].type == AIR);
				bool rightIsAir = (x + 1 >= CHUNK_X) ? true : (blocks[y][z][x + 1].type == AIR);
				bool leftIsAir = (x - 1 < 0) ? true : (blocks[y][z][x - 1].type == AIR);

				if (topIsAir)    AddFace(TOP, evaluatedBlock);
				if (bottomIsAir) AddFace(BOTTOM, evaluatedBlock);
				if (frontIsAir)  AddFace(FRONT, evaluatedBlock);
				if (backIsAir)   AddFace(BACK, evaluatedBlock);
				if (rightIsAir)  AddFace(RIGHT, evaluatedBlock);
				if (leftIsAir)   AddFace(LEFT, evaluatedBlock);
			}
		}
	}
	va.Bind();
	vb.UpdateData(vertexInfo.data(), vertexInfo.size() * sizeof(Vertex));
	ib.UpdateData(indexValues.data(), indexValues.size() * sizeof(unsigned int));
	va.AddBuffer(vb, vbl);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "1. ERROR IS: " << err << "\n";
	}
	//std::cout << faceNumber << "\n";
}

void Chunk::RenderChunk()
{
	va.Bind();
	ib.Bind();
	glActiveTexture(GL_TEXTURE0);
	textureGrid.Bind();
	glDrawElements(GL_TRIANGLES, indexValues.size(), GL_UNSIGNED_INT, nullptr);
}

bool Chunk::RemoveBlock(glm::vec3* blockToRemove)
{
	if (blocks[int(blockToRemove->y)][int(blockToRemove->z)][int(blockToRemove->x)].type == AIR) {
		return false;
	}
	//std::cout << "Block is removed at (" << blockToRemove->x << ", " << blockToRemove->y << ", " << blockToRemove->z << ")\n";
	blocks[int(blockToRemove->y)][int(blockToRemove->z)][int(blockToRemove->x)] = Block(*blockToRemove, AIR);
	RebuildMeshes();
	delete blockToRemove;
	return true;
}

glm::vec2* Chunk::GenerateUVCoords(Block& block, CubeFace face)
{
	static glm::vec2 uvCoordinates[4];
	BlockTextureInfo& info = BLOCK_DATABASE[block.type];
	glm::ivec2 tile;

	switch (face) {
	case TOP:		tile = info.uvTop;		break;
	case BOTTOM:	tile = info.uvSide;		break;
	default:		tile = info.uvBottom;	break;
	}

	switch (face)
	{
	case FRONT:  uvCoordinates[0] = AtlasUV({ 0,0 }, tile); uvCoordinates[1] = AtlasUV({ 0,1 }, tile); uvCoordinates[2] = AtlasUV({ 1,0 }, tile); uvCoordinates[3] = AtlasUV({ 1,1 }, tile); break;
	case BACK:   uvCoordinates[0] = AtlasUV({ 0,0 }, tile); uvCoordinates[1] = AtlasUV({ 1,0 }, tile); uvCoordinates[2] = AtlasUV({ 0,1 }, tile); uvCoordinates[3] = AtlasUV({ 1,1 }, tile); break;
	case LEFT:   uvCoordinates[0] = AtlasUV({ 0,0 }, tile); uvCoordinates[1] = AtlasUV({ 0,1 }, tile); uvCoordinates[2] = AtlasUV({ 1,0 }, tile); uvCoordinates[3] = AtlasUV({ 1,1 }, tile); break;
	case RIGHT:  uvCoordinates[0] = AtlasUV({ 0,0 }, tile); uvCoordinates[1] = AtlasUV({ 1,0 }, tile); uvCoordinates[2] = AtlasUV({ 0,1 }, tile); uvCoordinates[3] = AtlasUV({ 1,1 }, tile); break;
	case TOP:    uvCoordinates[0] = AtlasUV({ 0,0 }, tile); uvCoordinates[1] = AtlasUV({ 0,1 }, tile); uvCoordinates[2] = AtlasUV({ 1,0 }, tile); uvCoordinates[3] = AtlasUV({ 1,1 }, tile); break;
	case BOTTOM: uvCoordinates[0] = AtlasUV({ 0,0 }, tile); uvCoordinates[1] = AtlasUV({ 0,1 }, tile); uvCoordinates[2] = AtlasUV({ 1,0 }, tile); uvCoordinates[3] = AtlasUV({ 1,1 }, tile); break;
	}
	return uvCoordinates;
}

glm::vec2 Chunk::AtlasUV(glm::vec2 uv, glm::ivec2 tile)
{
	return {
		(uv.x + tile.x) * textureTileSize,
		(uv.y + tile.y) * textureTileSize
	};
}

void Chunk::AddFace(CubeFace face, Block& block)
{
	glm::vec3* positions = nullptr;
	glm::vec2* textCoords = GenerateUVCoords(block, face);

	if (face == TOP) {
		positions = topFacePos;
	}
	else if (face == BOTTOM) {
		positions = bottomFacePos;
	}
	else if (face == LEFT) {
		positions = leftFacePos;
	}
	else if (face == RIGHT) {
		positions = rightFacePos;
	}
	else if (face == FRONT) {
		positions = frontFacePos;
	}
	else if (face == BACK) {
		positions = backFacePos;
	}

	vertexInfo.push_back({ positions[0] + block.position + glm::vec3(chunkCoords.x * 16, 0, chunkCoords.y * 16), textCoords[0] });
	vertexInfo.push_back({ positions[1] + block.position + glm::vec3(chunkCoords.x * 16, 0, chunkCoords.y * 16), textCoords[1] });
	vertexInfo.push_back({ positions[2] + block.position + glm::vec3(chunkCoords.x * 16, 0, chunkCoords.y * 16), textCoords[2] });
	vertexInfo.push_back({ positions[3] + block.position + glm::vec3(chunkCoords.x * 16, 0, chunkCoords.y * 16), textCoords[3] });

	
	for (unsigned int index : indices) {
		indexValues.push_back((4 * faceNumber) + index);
	}
	faceNumber++;
}
