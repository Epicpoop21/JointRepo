#pragma once
#include "Renderer.h"
#include <vector>

struct VertexBufferElement {
	unsigned int count;
	unsigned int type;
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

//Used to contain information to put into vertex arrays per lot of vertices (one for positions, one for colours etc)
class VertexBufferLayout {
private:
	//
	unsigned int m_Stride;
	std::vector<VertexBufferElement> m_Elements;
public:
	VertexBufferLayout() : m_Stride(0) {};

	template<typename T>
	void Push(int count) {
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned int count) {
		m_Elements.push_back(count);
	}

private:

};