#pragma once

#include "Block.h"
#include "../rendering/VertexArray.h"
#include "../rendering/VertexBuffer.h"
#include "../rendering/VertexBufferLayout.h"
#include "../rendering/IndexBuffer.h"
#include "../rendering/Texture.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

class Chunk
{
public:
	Chunk(glm::vec2 origin, Texture& texture);
	~Chunk();
	void RebuildMeshes();
	void RenderChunk();
    bool RemoveBlock(glm::vec3* blockToRemove);
    glm::vec2* GenerateUVCoords(Block& block, CubeFace face);
    glm::vec2 AtlasUV(glm::vec2 uv, glm::ivec2 tile);
private:
	void AddFace(CubeFace face, Block& block);
public:
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
    Texture& textureGrid;
	VertexBufferLayout vbl;
    glm::vec2 chunkCoords;
private:
    static float textureTileSize;
	static const int CHUNK_X = 16;
	static const int CHUNK_Z = 16;
	static const int CHUNK_Y = 256;

	Block blocks[CHUNK_Y][CHUNK_Z][CHUNK_X];

    struct Vertex {
        glm::vec3 position;
        glm::vec2 texCoords;
    };
	std::vector<Vertex> vertexInfo;
	std::vector<unsigned int> indexValues;

	static unsigned int faceNumber;

    glm::vec3 topFacePos[4] = {
        {0.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    glm::vec3 bottomFacePos[4] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f}
    };

    glm::vec3 leftFacePos[4] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 1.0f}
    };

    glm::vec3 rightFacePos[4] = {
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    glm::vec3 frontFacePos[4] = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    glm::vec3 backFacePos[4] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f}
    };

    glm::vec2 baseTexCoords[4] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}
    };


	unsigned int indices[6] = {
		0, 1, 2,
		2, 1, 3
	};
};

