#pragma once
#include <glad/glad.h>

class ShaderStorageBuffer
{
public:
	ShaderStorageBuffer(const void* data, unsigned int nOfValues);
	~ShaderStorageBuffer();

	ShaderStorageBuffer(const ShaderStorageBuffer&) = delete;
	ShaderStorageBuffer& operator = (const ShaderStorageBuffer&) = delete;

	ShaderStorageBuffer(ShaderStorageBuffer&& other) noexcept
		:m_BufferID(other.m_BufferID) {
		other.m_BufferID = 0;
	}

	ShaderStorageBuffer& operator = (ShaderStorageBuffer&& other) noexcept {
		if (this != &other) {
			glDeleteBuffers(1, &m_BufferID);
			m_BufferID = other.m_BufferID;
			other.m_BufferID = 0;
		}
	}

	void Bind();
	static void Unbind();
	void UpdateData(const void* data, unsigned int nOfValues, GLenum useage);
private:

public:

private:
	unsigned int m_BufferID;
};

