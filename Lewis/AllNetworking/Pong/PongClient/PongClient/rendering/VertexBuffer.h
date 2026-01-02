#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int sizeInBytes);
	~VertexBuffer();

	void UpdateData(const void* data, unsigned int sizeInBytes);
	void Bind();
	static void Unbind();
private:

public:
	
private:
	unsigned int m_ID;
};

