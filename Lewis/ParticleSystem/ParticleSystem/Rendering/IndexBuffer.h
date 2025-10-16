#pragma once
#include "Renderer.h"

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int nOfValues);
	~IndexBuffer();

	void Bind();
	static void Unbind();
private:

public:

private:
	unsigned int m_BufferID;
};

