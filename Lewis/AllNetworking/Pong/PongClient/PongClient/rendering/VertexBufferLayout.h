#pragma once
#include <glad/glad.h>
#include <vector>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	bool normalised;

	static unsigned int GetCount(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
		}
	}
};

class VertexBufferLayout {
public:
	VertexBufferLayout() : m_Stride(0) {}
	~VertexBufferLayout() {}
	
	template <typename T> 
	void Push(unsigned int count) {
		static_assert(false);
	}

	template<>
	void Push<unsigned int>(unsigned int count) {
		elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetCount(GL_UNSIGNED_INT);
	}

	template<>
	void Push<float>(unsigned int count) {
		elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetCount(GL_FLOAT);
	}

	unsigned int GetStride() const { return m_Stride; }
	std::vector<VertexBufferElement> GetElements() const { return elements; }
private:

public:

private:
	//Stide between each set of values
	unsigned int m_Stride;
	std::vector<VertexBufferElement> elements;
};