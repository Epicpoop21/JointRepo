#pragma once
#include "Renderer.h"

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int nOfValues);
	~VertexBuffer();

	void Bind();
	static void Unbind();
private:

public:

private:
	unsigned int m_BufferID;
};

