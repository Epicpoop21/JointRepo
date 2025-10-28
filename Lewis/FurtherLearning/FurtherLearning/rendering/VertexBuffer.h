#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int bytes);
	~VertexBuffer();

	void Bind();
	static void Unbind();
private:

public:

private:
	unsigned int m_ObjectID;
};

