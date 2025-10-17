#include "VertexArray.h"
#include <iostream>
VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_BufferID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_BufferID);
}

void VertexArray::AddBuffer(const VertexBufferLayout* layout, VertexBuffer* vb)
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "[Checkpoint 2] OpenGL error: " << err << std::endl;
	}
	Bind();

	//vb.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalised, layout.GetStride(), (const void*)offset);
		/*std::cout << "Attrib " << i << ": count=" << element.count
			<< ", type=" << element.type
			<< ", normalized=" << element.normalised
			<< ", offset=" << offset << "\n"; */
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	//std::cout << "Stride = " << layout.GetStride() << "\n";
}

void VertexArray::Bind()
{
	glBindVertexArray(m_BufferID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

