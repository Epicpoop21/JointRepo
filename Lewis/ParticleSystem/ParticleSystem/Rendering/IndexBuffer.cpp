#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int sizeOfValues)
{
	glGenBuffers(1, &m_BufferID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfValues, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}




