#include "Shader.h"
#include <fstream>
#include <sstream>

void Shader::BuildGraphics(const char* vertexShaderFilePath, const char* fragementShaderFilePath)
{
	std::string vertexSource;
	std::string fragmentSource;

	std::ifstream vertexSourceFile;
	std::ifstream fragmentSourceFile;

	vertexSourceFile.exceptions(std::ifstream::failbit | std::fstream::badbit);
	fragmentSourceFile.exceptions(std::ifstream::failbit | std::fstream::badbit);

	try {
		vertexSourceFile.open(vertexShaderFilePath);
		fragmentSourceFile.open(fragementShaderFilePath);
		std::stringstream vertexStream, fragmentStream;

		vertexStream << vertexSourceFile.rdbuf();
		fragmentStream << fragmentSourceFile.rdbuf();

		vertexSourceFile.close();
		fragmentSourceFile.close();

		vertexSource = vertexStream.str();
		fragmentSource = fragmentStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "SHADER FILE READING ERROR. \n" << e.what() << "\n";
	}

	const char* vertexCode = vertexSource.c_str();
	const char* fragmentCode = fragmentSource.c_str();

	unsigned int vertexProgram, fragmentProgram;

	vertexProgram = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexProgram, 1, &vertexCode, NULL);
	glCompileShader(vertexProgram);
	CheckCompilerIssues(vertexProgram, "VERTEX");

	fragmentProgram = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentProgram, 1, &fragmentCode, NULL);
	glCompileShader(fragmentProgram);
	CheckCompilerIssues(fragmentProgram, "FRAGMENT");

	m_GraphicsID = glCreateProgram();
	glAttachShader(m_GraphicsID, vertexProgram);
	glAttachShader(m_GraphicsID, fragmentProgram);
	glLinkProgram(m_GraphicsID);
	CheckCompilerIssues(m_GraphicsID, "PROGRAM");

	glDeleteShader(vertexProgram);
	glDeleteShader(fragmentProgram);
}

void Shader::BuildCompute(const char* computShaderFilePath)
{
	if (computShaderFilePath == nullptr) {
		return;
	}
	std::string computeSource;
	std::ifstream computeSourceFile;
	computeSourceFile.exceptions(std::ifstream::failbit | std::fstream::badbit);

	try {
		computeSourceFile.open(computShaderFilePath);
		std::stringstream computeStream;
		computeStream << computeSourceFile.rdbuf();

		computeSourceFile.close();

		computeSource = computeStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "SHADER FILE READING ERROR. \n" << e.what() << "\n";
	}
	const char* computeCode = computeSource.c_str();

	unsigned int computeProgram;
	computeProgram = glCreateShader(GL_COMPUTE_SHADER);
	glShaderSource(computeProgram, 1, &computeCode, NULL);
	glCompileShader(computeProgram);
	CheckCompilerIssues(computeProgram, "COMPUTE");

	m_ComputeID = glCreateProgram();
	glAttachShader(m_ComputeID, computeProgram);
	glLinkProgram(m_ComputeID);
	CheckCompilerIssues(m_ComputeID, "PROGRAM");

	glDeleteShader(computeProgram);
}

Shader::Shader(const char* vertexShaderFilePath, const char* fragementShaderFilePath, const char* computeShaderFilePath)
{
	BuildGraphics(vertexShaderFilePath, fragementShaderFilePath);
	BuildCompute(computeShaderFilePath);
}

Shader::~Shader()
{
	
}

void Shader::UseGraphics()
{
	glUseProgram(m_GraphicsID);
	currentShaderBound = GraphicsShader;
}

void Shader::UseCompute()
{
	glUseProgram(m_ComputeID);
	currentShaderBound = ComputeShader;
}

void Shader::SetBool(const std::string& uniformName, bool v0)
{
	glUniform1i(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0);
}

void Shader::SetFloat(const std::string& uniformName, float v0)
{
	glUniform1f(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0);
}

void Shader::SetInt(const std::string& uniformName, int v0)
{
	glUniform1i(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0);
}

void Shader::SetVec2f(const std::string& uniformName, float v0, float v1)
{
	glUniform2f(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0, v1);
}

void Shader::SetVec2fv(const std::string& uniformName, int size, float* value)
{
	glUniform2fv(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), size, value);
}

void Shader::SetVec3f(const std::string& uniformName, float v0, float v1, float v2)
{
	glUniform3f(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0, v1, v2);
}

void Shader::SetVec4f(const std::string& uniformName, float v0, float v1, float v2, float v3)
{
	glUniform4f(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0, v1, v2, v3);
}

void Shader::SetMat4f(const std::string& uniformName, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

unsigned int Shader::ReturnShaderID(ShaderType type)
{
	if (type == ComputeShader) {
		return m_ComputeID;
	}
	else if (type == GraphicsShader) {
		return m_GraphicsID;
	}
}

void Shader::CheckCompilerIssues(unsigned int shader, std::string shaderType)
{
	int success;
	char infoLog[1024];
	if (shaderType != "PROGRAM") {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER OF TYPE " << shaderType << " COMPILATION ERROR. \n" << infoLog << "\n";
		}
	}
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "SHADER OF TYPE " << shaderType << " COMPILATION ERROR. \n" << infoLog << "\n";
		}
	}
}