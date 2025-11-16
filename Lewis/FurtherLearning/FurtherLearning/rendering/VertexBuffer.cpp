#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int bytes)
{
	glGenBuffers(1, &m_ObjectID);
	Bind();
	if (data != nullptr && bytes != 0) {
		glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
	}
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_ObjectID);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_ObjectID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::UpdateData(const void* data, unsigned int bytes)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, bytes, data, GL_STATIC_DRAW);
	Unbind();
}
