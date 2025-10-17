#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer() = default;
	VertexBuffer(const void* data, unsigned int nOfValues);
	~VertexBuffer();

	void Bind();
	static void Unbind();
private:

public:

private:
	unsigned int m_BufferID;
};

