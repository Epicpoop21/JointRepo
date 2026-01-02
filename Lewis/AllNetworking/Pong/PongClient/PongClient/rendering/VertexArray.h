#pragma once
#include <glad/glad.h>
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind();
	static void Unbind();
	void AddBuffer(VertexBufferLayout& vbl, VertexBuffer& vb);
private:

public:

private:
	unsigned int m_ID;
};

