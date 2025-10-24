#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "ShaderStorageBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct RenderInfo {
	VertexArray va;
	VertexBuffer quadVB;
	IndexBuffer ib;
	VertexBufferLayout vbl1;
	VertexBufferLayout vbl2;
	ShaderStorageBuffer ssb;

	RenderInfo(VertexArray&& va, VertexBuffer&& quadVB, IndexBuffer&& ib, VertexBufferLayout&& vbl1, VertexBufferLayout&& vbl2, ShaderStorageBuffer&& ssb)
		: va(std::move(va)), quadVB(std::move(quadVB)), vbl1(std::move(vbl1)), vbl2(std::move(vbl2)), ib(std::move(ib)), ssb(std::move(ssb)) {
	}
};

struct Coordinate {
	float xCoord;
	float yCoord;
};

class Renderer
{
};

