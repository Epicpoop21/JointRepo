#pragma once
#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int sizeInBytes);
	~IndexBuffer();

	void UpdateData(const void* data, unsigned int sizeInBytes);
	void Bind();
	static void Unbind();
private:

public:

private:
	unsigned int m_ID;
};

