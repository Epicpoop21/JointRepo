#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include "../game/Chunk.h"

#include <vector>

class CubeRenderer {
public:
	static CubeRenderer* GetInstance();

	CubeRenderer();
	~CubeRenderer();

	static void Render();
	static int GetChunkIndexByWorldCoords(glm::vec3 coords);
	static void RemoveBlock();
private:

public:

private:
	inline static std::unique_ptr<CubeRenderer> s_Instance;

	static inline std::vector<std::unique_ptr<Chunk>> chunks;
	static inline int renderDistance = 2;
};