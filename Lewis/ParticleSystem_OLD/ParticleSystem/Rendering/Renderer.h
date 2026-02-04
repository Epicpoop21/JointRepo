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
	VertexBufferLayout vbl1;
	VertexBufferLayout vbl2;

	RenderInfo(VertexArray&& va, VertexBuffer&& quadVB, VertexBuffer&& instanceVB, IndexBuffer&& ib, VertexBufferLayout&& vbl1, VertexBufferLayout&& vbl2)
		: va(std::move(va)), quadVB(std::move(quadVB)), instanceVB(std::move(instanceVB)), vbl1(std::move(vbl1)), vbl2(std::move(vbl2)), ib(std::move(ib)) {
	}
};

struct Coordinate {
	float xCoord;
	float yCoord;
};

class Renderer
{
};

