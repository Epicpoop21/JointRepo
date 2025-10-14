#pragma once
#include "Renderer.h"

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexShaderFilePath, const char* fragementShaderFilePath);
	~Shader();

	void Use();

private:
	void CheckCompilerIssues(unsigned int shader, std::string shaderType);
public:

private:
	unsigned int m_ShaderID;
};

