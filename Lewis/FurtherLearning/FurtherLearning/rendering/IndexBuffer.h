#pragma once
#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int bytes);
	~IndexBuffer();

	void Bind();
	static void Unbind();
private:

public:

private:
	unsigned int m_ObjectID;
};

