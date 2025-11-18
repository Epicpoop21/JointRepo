#include "Chunk.h"

Chunk::Chunk(glm::vec2 origin) : vb(nullptr, 0), ib(nullptr, 0), faceNumber(0)
{
	this->chunkCoords = origin;
	for (int z = 0; z < 16; z++) {
		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 2; y++) {
				blocks[y][z][x] = Block(glm::vec3(x, y, z), GRASS);
			}
		}
	}
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
	vb.UpdateData(vertexInfo.data(), vertexInfo.size() * sizeof(Vertex));
	ib.UpdateData(indexValues.data(), indexValues.size() * sizeof(unsigned int));
	va.AddBuffer(vb, vbl);
	//std::cout << faceNumber << "\n";
}

void Chunk::RenderChunk()
{
	va.Bind();
	ib.Bind();
	glActiveTexture(GL_TEXTURE0);
	ct.GetTexture(DIRT).Bind();
	glDrawElements(GL_TRIANGLES, indexValues.size(), GL_UNSIGNED_INT, nullptr);
}

void Chunk::RemoveBlock(glm::vec3 blockToRemove)
{
	blocks[int(blockToRemove.y)][int(blockToRemove.z)][int(blockToRemove.x)] = Block(blockToRemove, AIR);
	RebuildMeshes();
}

void Chunk::AddFace(CubeFace face, Block& block)
{
	glm::vec3* positions = nullptr;
	glm::vec2* textCoords = nullptr;
	if (face == TOP) {
		positions = topFacePos;
		textCoords = topFaceTex;
	}
	else if (face == BOTTOM) {
		positions = bottomFacePos;
		textCoords = bottomFaceTex;
	}
	else if (face == LEFT) {
		positions = leftFacePos;
		textCoords = leftFaceTex;
	}
	else if (face == RIGHT) {
		positions = rightFacePos;
		textCoords = rightFaceTex;
	}
	else if (face == FRONT) {
		positions = frontFacePos;
		textCoords = frontFaceTex;
	}
	else if (face == BACK) {
		positions = backFacePos;
		textCoords = backFaceTex;
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
