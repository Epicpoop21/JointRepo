#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator = (const VertexArray&) = delete;

	VertexArray(VertexArray&& other) noexcept
		:m_BufferID(other.m_BufferID) {
		other.m_BufferID = 0;
	}

	VertexArray& operator = (VertexArray&& other) noexcept {
		if (this != &other) {
			glDeleteVertexArrays(1, &m_BufferID);
			m_BufferID = other.m_BufferID;
			other.m_BufferID = 0;
		}
	}

	void AddBuffer(const VertexBufferLayout& layout, VertexBuffer& vb);
	void Bind();
	static void Unbind();
private:

public:
	unsigned int m_BufferID;
private:

};

