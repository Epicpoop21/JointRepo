#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	~Shader();

	void Use();

	void SetFloat(const std::string& name, float value);
	void SetInt(const std::string& name, int value);
	void SetBool(const std::string& name, bool value);
	void SetVec2f(const std::string& name, float v0, float v1);
	void SetVec3f(const std::string& name, float v0, float v1, float v2);
	void SetVec4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetMat4f(const std::string& name, glm::mat4 mat);
private:
	void CheckCompilationIssues(unsigned int shaderID, const char* shaderType);
public:

private:
	unsigned int m_ShaderID;
};

