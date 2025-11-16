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
	CubeRenderer();
	~CubeRenderer();
	void Render();
private:

public:

private:
	std::unique_ptr<Chunk> chunk;
};