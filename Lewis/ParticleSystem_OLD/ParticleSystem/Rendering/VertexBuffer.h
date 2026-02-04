#pragma once
#include <glad/glad.h>

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned int nOfValues, GLenum useage);
	~VertexBuffer();

	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator = (const VertexBuffer&) = delete;

	VertexBuffer(VertexBuffer&& other) noexcept
		:m_BufferID(other.m_BufferID) {
		other.m_BufferID = 0;
	}

	VertexBuffer& operator = (VertexBuffer&& other) noexcept {
		if (this != &other) {
			glDeleteBuffers(1, &m_BufferID);
			m_BufferID = other.m_BufferID;
			other.m_BufferID = 0;
		}
	}

	void Bind();
	static void Unbind();
	void UpdateData(const void* data, unsigned int nOfValues, GLenum useage);
private:

public:

private:
	unsigned int m_BufferID;
};

