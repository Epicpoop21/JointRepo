#pragma once
#include <glad/glad.h>
#include "VertexBufferLayout.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void ResetBuffer();
	void AddBuffer(VertexBuffer &vb, VertexBufferLayout& layout);
	void Bind();
	static void Unbind();
private:

public:

private:
	unsigned int m_ObjectID;
	unsigned int m_Index;
};

