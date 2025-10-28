#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_ObjectID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_ObjectID);
}

void VertexArray::AddBuffer(VertexBuffer vb, VertexBufferLayout layout)
{
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	for (int i = 0; i < layout.GetElements().size(); i++) {
		VertexBufferElement element = layout.GetElements()[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), (void*)offset);
		glEnableVertexAttribArray(i);
		offset += element.count * VertexBufferElement::GetCount(element.type);
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
