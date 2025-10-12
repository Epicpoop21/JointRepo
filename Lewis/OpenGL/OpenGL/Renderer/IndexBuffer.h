#pragma once

class IndexBuffer {
public:

private:
	unsigned int ID;
public:
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();

	//Deletes copy constructor and removes ability to copy
	IndexBuffer(const IndexBuffer&) = delete;
	IndexBuffer& operator = (const IndexBuffer&) = delete;

	//Move constructor
	IndexBuffer(IndexBuffer&& other) noexcept
		:ID(other.ID) {
		other.ID = 0; //Scrap other one
	}
	//Move assignment
	IndexBuffer& operator = (IndexBuffer&& other) noexcept {
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