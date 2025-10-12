#include "shader.h"
#include "Renderer.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertexSourcePath, const char* fragmentSourcePath)
{
	std::string vertexCode;
	std::string fragmentCode;
	
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vertexSourcePath);
		fShaderFile.open(fragmentSourcePath);
		std::stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e) {
		std::cout << "SHADER FILE ERROR. \n" << e.what() << "\n";
	}
	const char* vertexSource = vertexCode.c_str();
	const char* fragmentSource = fragmentCode.c_str();

	unsigned int vertexShader, fragmentShader;

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	CheckCompilerIssues(vertexShader, "VERTEX");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	CheckCompilerIssues(fragmentShader, "FRAGMENT");

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	CheckCompilerIssues(shaderProgram, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{

}

void Shader::Use()
{
	glUseProgram(shaderProgram);
}

void Shader::SetFloatVec2(const std::string& name, float v0, float v1)
{
	glUniform2f(glGetUniformLocation(shaderProgram, name.c_str()), v0, v1);
}

void Shader::SetFloatVec4(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), v0, v1, v2, v3);
}

void Shader::SetFloatMat4(const std::string& name, float numOfValues, bool transpose, const float* values)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), numOfValues, transpose, values);
}

void Shader::SetFloatVec3(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), v0, v1, v2);
}

void Shader::SetFloat(const std::string& name, float v0)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), v0);
}

void Shader::SetBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int) value);
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
