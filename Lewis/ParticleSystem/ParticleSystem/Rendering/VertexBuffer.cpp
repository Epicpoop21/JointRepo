#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int sizeOfValues, GLenum useage)
{
	glGenBuffers(1, &m_BufferID);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeOfValues, data, useage);
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

void VertexBuffer::UpdateData(const void* data, unsigned int sizeOfValues, GLenum useage)
{
	glBufferData(GL_ARRAY_BUFFER, sizeOfValues, data, useage);
}





