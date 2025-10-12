#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray {
public:
	
private:
	unsigned int ID;
	VertexBufferLayout layout;
public:
	VertexArray();
	~VertexArray();

	//Deletes copy constructor and removes ability to copy
	VertexArray(const VertexArray&) = delete;
	VertexArray& operator = (const VertexArray&) = delete;

	//Move constructor
	VertexArray(VertexArray&& other) noexcept
		:ID(other.ID) {
		other.ID = 0; //Scrap other one
	}
	//Move assignment
	VertexArray& operator = (VertexArray&& other) noexcept {
		if (this != &other) {
			glDeleteVertexArrays(1, &ID);
			ID = other.ID;
			other.ID = 0;
		}
	}

	void Bind();
	void Unbind();

	void AddBuffer(VertexBuffer& vb, const VertexBufferLayout& layout);
private:

};