#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeOfValues)
{
	glGenBuffers(1, &m_BufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeOfValues, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}




