#pragma once
#include <glad/glad.h>
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Use();

private:
	void CheckErrors(std::string shaderType, unsigned int shaderProgram);

public:

private:
	unsigned int m_ProgramID;
	unsigned int m_VShaderID;
	unsigned int m_FShaderID;
};

