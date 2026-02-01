#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexShaderSource;
	std::string fragmentShaderSource;

	std::ifstream vertexStream;
	std::ifstream fragmentStream;

	vertexStream.open(vertexPath);
	fragmentStream.open(fragmentPath);

	std::stringstream vertexSS, fragmentSS;

	vertexSS << vertexStream.rdbuf();
	fragmentSS << fragmentStream.rdbuf();

	vertexStream.close();
	fragmentStream.close();

	vertexShaderSource = vertexSS.str();
	fragmentShaderSource = fragmentSS.str();

	const char* vShaderCString = vertexShaderSource.c_str();
	const char* fShaderCString = fragmentShaderSource.c_str();

	m_VShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_VShaderID, 1, &vShaderCString, NULL);
	glCompileShader(m_VShaderID);
	CheckErrors("VERTEX", m_VShaderID);

	m_FShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_FShaderID, 1, &fShaderCString, NULL);
	glCompileShader(m_FShaderID);
	CheckErrors("FRAGMENT", m_FShaderID);

	m_ProgramID = glCreateProgram();
	glAttachShader(m_ProgramID, m_VShaderID);
	glAttachShader(m_ProgramID, m_FShaderID);
	glLinkProgram(m_ProgramID);
	CheckErrors("PROGRAM", m_ProgramID);

	glDeleteShader(m_VShaderID);
	glDeleteShader(m_FShaderID);
}

Shader::~Shader()
{
}

void Shader::Use() {
	glUseProgram(m_ProgramID);
}

void Shader::CheckErrors(std::string shaderType, unsigned int shaderProgram)
{
	int success;
	char infoLog[1024];
	if (shaderType != "PROGRAM") {
		glGetShaderiv(shaderProgram, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderProgram, 1024, NULL, infoLog);
			std::cout << "ERROR WITH " << shaderType << " SHADER " << "\n" << infoLog << "\n";
		}
	}
	else {
		glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_ProgramID, 1024, NULL, infoLog);
			std::cout << "ERROR WITH PROGRAM " << infoLog << "\n";
		}
	}
}
