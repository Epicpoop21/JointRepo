#pragma once
#include <glad/glad.h>

class VertexBuffer {
public:

private: 
	unsigned int ID;
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	//Deletes copy constructor and removes ability to copy
	VertexBuffer(const VertexBuffer&) = delete;
	VertexBuffer& operator = (const VertexBuffer&) = delete;

	//Move constructor
	VertexBuffer(VertexBuffer&& other) noexcept
		:ID(other.ID) {
		other.ID = 0; //Scrap other one
	}
	//Move assignment
	VertexBuffer& operator = (VertexBuffer&& other) noexcept {
		if (this != &other) {
			glDeleteBuffers(1, &ID);
			ID = other.ID;
			other.ID = 0;
		}
	}

	void Bind();
	void Unbind();
private:

};
