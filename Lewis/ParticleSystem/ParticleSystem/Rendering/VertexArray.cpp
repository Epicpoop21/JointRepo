#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_BufferID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_BufferID);
}

void VertexArray::AddBuffer(const VertexBufferLayout& layout, VertexBuffer& vb)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), (const void*)(uintptr_t)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	vb.Unbind();
	Unbind();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_BufferID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

