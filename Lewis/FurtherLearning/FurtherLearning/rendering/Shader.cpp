#include "Shader.h"

Shader::Shader(const char* vertexShaderFilePath, const char* fragmentShaderFilePath)
{
	std::string vertexCode;
	std::string fragmentCode;

	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		vShaderFile.open(vertexShaderFilePath);
		fShaderFile.open(fragmentShaderFilePath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR SHADER FILE NOT SUCCESSFULLY READ \n";
		
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	CheckCompilationIssues(vertexShader, "VERTEX");

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	CheckCompilationIssues(fragmentShader, "FRAGMENT");

	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, vertexShader);
	glAttachShader(m_ShaderID, fragmentShader);
	glLinkProgram(m_ShaderID);
	CheckCompilationIssues(m_ShaderID, "PROGRAM");

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
}

void Shader::Use()
{
	glUseProgram(m_ShaderID);
}

void Shader::SetFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}

void Shader::SetInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}

void Shader::SetBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}

void Shader::SetVec2f(const std::string& name, float v0, float v1)
{
	glUniform2f(glGetUniformLocation(m_ShaderID, name.c_str()), v0, v1);
}

void Shader::SetVec3f(const std::string& name, float v0, float v1, float v2)
{
	glUniform3f(glGetUniformLocation(m_ShaderID, name.c_str()), v0, v1, v2);
}

void Shader::SetVec4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(glGetUniformLocation(m_ShaderID, name.c_str()), v0, v1, v2, v3);
}

void Shader::SetMat4f(const std::string& name, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}


void Shader::CheckCompilationIssues(unsigned int shaderID, const char* shaderType)
{
	int success;
	char infoLog[1024];
	if (shaderType != "PROGRAM") {
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << shaderType << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << "\n";
		}
	}
	else {
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << shaderType << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << "\n";
		}
	}
}
