#pragma once
#include <string>

class Shader {
public:
	Shader() = default;
	Shader(const char* vertexSourcePath, const char* fragmentSourcePath);
	~Shader();
	void Use();
	void SetFloatVec2(const std::string& name, float v0, float v1);
	void SetFloatVec3(const std::string& name, float v0, float v1, float v2);
	void SetFloatVec4(const std::string& name, float v0, float v1, float v2, float v3);
	void SetFloatMat4(const std::string& name, float numOfValues, bool transpose, const float* values);
	void SetFloat(const std::string& name, float v0);
	void SetBool(const std::string& name, bool v0);
private:
	void CheckCompilerIssues(unsigned int shader, std::string shaderType);
public:
private:
	unsigned int shaderProgram;
};