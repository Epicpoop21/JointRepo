#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void AddBuffer(const VertexBufferLayout* layout, VertexBuffer* vb);
	void Bind();
	static void Unbind();
private:

public:
	unsigned int m_BufferID;
private:

};

