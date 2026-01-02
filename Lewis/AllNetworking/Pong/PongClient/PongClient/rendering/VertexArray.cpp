#include "VertexArray.h"

VertexArray::VertexArray() : m_ID(0)
{
	glGenVertexArrays(1, &m_ID);
}

VertexArray::~VertexArray()
{

}

void VertexArray::Bind() {
	glBindVertexArray(m_ID);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBufferLayout& vbl, VertexBuffer& vb)
{
	Bind();
	vb.Bind();
	unsigned int offset = 0;
	for (int i = 0; i < vbl.GetElements().size(); i++) {
		VertexBufferElement element = vbl.GetElements()[i];
		glVertexAttribPointer(i, element.count, element.type, element.normalised, vbl.GetStride(), (void*)offset);
		glEnableVertexAttribArray(i);

		offset += element.count * VertexBufferElement::GetCount(element.type);
	}
	vb.Unbind();
	Unbind();
}

