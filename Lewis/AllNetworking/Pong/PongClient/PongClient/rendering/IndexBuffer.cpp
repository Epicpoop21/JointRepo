#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int sizeInBytes) : m_ID(0)
{
	glGenBuffers(1, &m_ID);
	if (data != nullptr) {
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
	}
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::UpdateData(const void* data, unsigned int sizeInBytes)
{
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInBytes, data, GL_STATIC_DRAW);
	Unbind();
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
