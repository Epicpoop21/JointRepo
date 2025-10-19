#pragma once
#include <glad/glad.h>

class IndexBuffer
{
public:
	IndexBuffer(const void* data, unsigned int nOfValues);
	~IndexBuffer();

	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator = (const IndexBuffer&) = delete;

	IndexBuffer(IndexBuffer&& other) noexcept
		:m_BufferID(other.m_BufferID) {
		other.m_BufferID = 0;
	}

	IndexBuffer& operator = (IndexBuffer&& other) noexcept {
		if (this != &other) {
			glDeleteBuffers(1, &m_BufferID);
			m_BufferID = other.m_BufferID;
			other.m_BufferID = 0;
		}
	}

	void Bind();
	static void Unbind();
private:

public:

private:
	unsigned int m_BufferID;
};

