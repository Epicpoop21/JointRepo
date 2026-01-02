#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeInBytes) : m_ID(0)
{
	glGenBuffers(1, &m_ID);
	if (data != nullptr) {
		Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
	}
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ID);
}

void VertexBuffer::UpdateData(const void* data, unsigned int sizeInBytes)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
	Unbind();
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
