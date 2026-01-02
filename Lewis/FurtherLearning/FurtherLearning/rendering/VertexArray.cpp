#include "VertexArray.h"
#include <iostream>
VertexArray::VertexArray() : m_Index(0)
{
	glGenVertexArrays(1, &m_ObjectID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ObjectID);
}

void VertexArray::ResetBuffer()
{
	m_Index = 0;
	m_ObjectID = 0;
}

void VertexArray::AddBuffer(VertexBuffer &vb, VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	for (int i = 0; i < layout.GetElements().size(); i++) {
		VertexBufferElement element = layout.GetElements()[i];
		glVertexAttribPointer(m_Index, element.count, element.type, element.normalised, layout.GetStride(), (const void*)(uintptr_t)offset);
		glEnableVertexAttribArray(m_Index);

		offset += element.count * VertexBufferElement::GetCount(element.type);
		m_Index++;
	}
	vb.Unbind();
	Unbind();
}



void VertexArray::Bind()
{
	glBindVertexArray(m_ObjectID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}
