#pragma once
#include <vector>

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	bool normalised;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT: return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		return 0;
	}
};

//Used to contain information to put into vertex arrays per lot of vertices 
//Each VertexBufferLayout contains many VertexBufferElement (One for each attribute, ie colour, position etc)
class VertexBufferLayout {
private:
	//Stride in bytes. (Number of bytes per value * number of values)
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;
public:
	VertexBufferLayout() : m_Stride(0) {};

	//Fallback function for any types that haven't been specified; it'll cause an error
	template<typename T>
	void Push(unsigned int count) {
		static_assert(false);
	}

	//For all 3 functions, add a certain amount of elements to the layout together

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	} 

	template<>
	void Push<unsigned int>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });		
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count) {
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	std::vector<VertexBufferElement> GetElements() const {
		return m_Elements;
	}

	unsigned int GetStride() const {
		return m_Stride;
	}
private:

};