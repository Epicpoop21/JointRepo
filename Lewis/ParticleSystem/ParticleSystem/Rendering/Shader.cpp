#include "Shader.h"
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexShaderFilePath, const char* fragementShaderFilePath)
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

	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, vertexProgram);
	glAttachShader(m_ShaderID, fragmentProgram);
	glLinkProgram(m_ShaderID);
	CheckCompilerIssues(m_ShaderID, "PROGRAM");

	glDeleteShader(vertexProgram);
	glDeleteShader(fragmentProgram);
}

Shader::~Shader()
{
}

void Shader::Use()
{
	glUseProgram(m_ShaderID);
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