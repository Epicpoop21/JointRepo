#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int bytes)
{
	glGenBuffers(1, &m_ObjectID);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_ObjectID);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ObjectID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::UpdateData(const void* data, unsigned int bytes)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
	Unbind();
}