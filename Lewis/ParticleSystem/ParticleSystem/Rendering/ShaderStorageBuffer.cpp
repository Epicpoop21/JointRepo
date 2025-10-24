#include "ShaderStorageBuffer.h"

ShaderStorageBuffer::ShaderStorageBuffer(const void* data, unsigned int sizeOfValues)
{
	glGenBuffers(1, &m_BufferID);
	Bind();
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeOfValues, data, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_BufferID);
}

ShaderStorageBuffer::~ShaderStorageBuffer()
{
	glDeleteBuffers(1, &m_BufferID);
}

void ShaderStorageBuffer::Bind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_BufferID);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, m_BufferID);
}

void ShaderStorageBuffer::Unbind()
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBuffer::UpdateData(const void* data, unsigned int sizeOfValues, GLenum useage)
{
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeOfValues, data, useage);
}





