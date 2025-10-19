#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct RenderInfo {
	VertexArray va;
	VertexBuffer quadVB;
	VertexBuffer instanceVB;
	IndexBuffer ib;
	VertexBufferLayout vbl;

	RenderInfo(VertexArray&& va, VertexBuffer&& quadVB, VertexBuffer&& instanceVB, IndexBuffer&& ib, VertexBufferLayout&& vbl)
		: va(std::move(va)), quadVB(std::move(quadVB)), instanceVB(std::move(instanceVB)), vbl(std::move(vbl)), ib(std::move(ib)) {
	}
};

struct Coordinate {
	float xCoord;
	float yCoord;
};

class Renderer
{
};

