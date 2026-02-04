#pragma once
#include "Renderer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
	Shader() = default;
	Shader(const char* vertexShaderFilePath, const char* fragementShaderFilePath);
	~Shader();

	void Use();

	void SetBool(const std::string& uniformName, bool v0);
	void SetFloat(const std::string& uniformName, float v0);
	void SetInt(const std::string& uniformName, int v0);
	void SetVec2f(const std::string& uniformName, float v0, float v1);
	void SetVec2fv(const std::string& uniformName, int size, float* value);
	void SetVec3f(const std::string& uniformName, float v0, float v1, float v2);
	void SetVec4f(const std::string& uniformName, float v0, float v1, float v2, float v3);
	void SetMat4f(const std::string& uniformName, glm::mat4 mat);

private:
	void CheckCompilerIssues(unsigned int shader, std::string shaderType);
public:

private:
	unsigned int m_ShaderID;
};

