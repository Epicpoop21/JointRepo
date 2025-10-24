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

	glUseProgram(m_GraphicsID);
	glUseProgram(0);
	glFinish();
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

	UseCompute();
	glDispatchCompute(1, 1, 1);
	glMemoryBarrier(GL_ALL_BARRIER_BITS);
	glUseProgram(0);
	glFinish();
}

Shader::Shader(const char* vertexShaderFilePath, const char* fragementShaderFilePath, const char* computeShaderFilePath)
{
	m_ComputeID = 0;
	m_GraphicsID = 0;
	currentShaderBound = NoneBound;

	BuildGraphics(vertexShaderFilePath, fragementShaderFilePath);
	BuildCompute(computeShaderFilePath);

	std::cout << "Graphics shader ID is: " << m_GraphicsID << "\n";
	std::cout << "Compute shader ID is: " << m_ComputeID << "\n";
}

Shader::~Shader()
{
	
}

void Shader::UseGraphics()
{
	if (m_GraphicsID != 0) {
		glUseProgram(m_GraphicsID);
	}
	else {
		std::cout << "Failed to use graphics program \n";
	}
	currentShaderBound = GraphicsShader;
}

void Shader::UseCompute()
{
	if (m_ComputeID != 0) {
		glUseProgram(m_ComputeID);
	}
	else {
		std::cout << "Failed to use compute program \n";
	}
	currentShaderBound = ComputeShader;
}

void Shader::SetBool(const std::string& uniformName, bool v0)
{
	if (ReturnShaderID(currentShaderBound) != 0) {
		glUniform1i(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0);
	}
}

void Shader::SetFloat(const std::string& uniformName, float v0)
{
	if (ReturnShaderID(currentShaderBound) != 0) {
		glUniform1f(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0);
	}
}

void Shader::SetInt(const std::string& uniformName, int v0)
{
	if (ReturnShaderID(currentShaderBound) != 0) {
		glUniform1i(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0);
	}
}

void Shader::SetVec2f(const std::string& uniformName, float v0, float v1)
{
	if (ReturnShaderID(currentShaderBound) != 0) {
		glUniform2f(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0, v1);
	}
}

void Shader::SetVec2fv(const std::string& uniformName, int size, float* value)
{
	if (ReturnShaderID(currentShaderBound) != 0) {
		glUniform2fv(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), size, value);
	}
}

void Shader::SetVec3f(const std::string& uniformName, float v0, float v1, float v2)
{
	if (ReturnShaderID(currentShaderBound) != 0) {
		glUniform3f(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0, v1, v2);
	}
}

void Shader::SetVec4f(const std::string& uniformName, float v0, float v1, float v2, float v3)
{
	if (ReturnShaderID(currentShaderBound) != 0) {
		glUniform4f(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), v0, v1, v2, v3);
	}
}

void Shader::SetMat4f(const std::string& uniformName, glm::mat4 mat)
{
	if (ReturnShaderID(currentShaderBound) != 0) {
		glUniformMatrix4fv(glGetUniformLocation(ReturnShaderID(currentShaderBound), uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
	}
}

unsigned int Shader::ReturnShaderID(ShaderType type)
{
	if (type == ComputeShader) {
		return m_ComputeID;
	}
	else if (type == GraphicsShader) {
		return m_GraphicsID;
	}
	else {
		return 0;
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