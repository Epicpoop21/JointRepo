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
	Chunk();
	~Chunk();
	void RebuildMeshes();
	void RenderChunk();
private:
	void AddFace(CubeFace face, Block& block);
public:
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
    Texture texture;
	VertexBufferLayout vbl;
private:
	glm::vec3 origin;

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

	unsigned int faceNumber;

    glm::vec3 topFacePos[4] = {
        {0.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    glm::vec2 topFaceTex[4] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}
    };

    glm::vec3 bottomFacePos[4] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f}
    };

    glm::vec2 bottomFaceTex[4] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}
    };

    glm::vec3 leftFacePos[4] = {
        {0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 1.0f}
    };

    glm::vec2 leftFaceTex[4] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}
    };

    glm::vec3 rightFacePos[4] = {
        {1.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 1.0f}
    };

    glm::vec2 rightFaceTex[4] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}
    };

    glm::vec3 frontFacePos[4] = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 1.0f},
        {1.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 1.0f}
    };

    glm::vec2 frontFaceTex[4] = {
        {0.0f, 0.0f},
        {0.0f, 1.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f}
    };

    glm::vec3 backFacePos[4] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f},
        {1.0f, 1.0f, 0.0f}
    };

    glm::vec2 backFaceTex[4] = {
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

