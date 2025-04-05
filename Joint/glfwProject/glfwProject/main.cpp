#include <glad/glad.h> 
#include <GLFW3/glfw3.h>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "shaders.h"
#include "projectHeader.h"

using namespace std;

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void checkShaderSucess(unsigned int shader);
void createShader(unsigned int* shader, const char** shaderSource, GLenum shaderType);
int cosineMultiplier = 0;
xyCoords coords[362];

int i = 0;
int n = 0;

int main() {
	std::cout << "Enter the cosine multiplier: ";
	std::cin >> cosineMultiplier;

	cosineWave(cosineMultiplier, &coords[0]);

	//GLFW configuration and initialisation 
	glfwInit();
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

	GLFWmonitor* primary = glfwGetPrimaryMonitor();

	//GLFW window creation
	GLFWwindow* window = glfwCreateWindow(2560, 1440, "Window", primary, NULL);
	if (window == NULL) {
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	//Load all OpenGL function pointers to hardware using GLAD library
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
	
	Shader fileShader("vertexShader.vs", "fragShader.fs");
	
	vector<float> graphVertices;
	for (n = 0; n < 2560; n+=360) {
		for (i = 0; i < 361; i++) {
			//std::cout << "Coords at point " + std::to_string(i) + " are " + std::to_string((coords[i].x - 1440 + n) / 1440.0f) + "\n";
			graphVertices.push_back((coords[i].x - 1440 + n) / 1440.0f);
			//std::cout << "Coords at point " + std::to_string(i) + " are " + std::to_string(coords[i].y / 40.0f) + "\n" + "\n";
			graphVertices.push_back(coords[i].y / 20.0);
		}
	}
	
	unsigned int graphVAO, textureVAO, graphVBO, textureVBO, EBO;
	glGenVertexArrays(1, &graphVAO);
	glGenVertexArrays(1, &textureVAO);
	glGenBuffers(1, &graphVBO);
	glGenBuffers(1, &textureVBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(graphVAO);
	glBindBuffer(GL_ARRAY_BUFFER, graphVBO);
	glBufferData(GL_ARRAY_BUFFER, graphVertices.size() * sizeof(float), graphVertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	float vertices[] = {
		-1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f,  0.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,  0.0f,
		 1.0f,  1.0f,  1.0f,  1.0f
	};
	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	glBindVertexArray(textureVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);


	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("graphTemplate.jpg", &width, &height, &nrChannels, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);



	fileShader.use();

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.0f, 0.8f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUniform1i(glGetUniformLocation(fileShader.ID, "useBlack"), 0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(textureVAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glUniform1i(glGetUniformLocation(fileShader.ID, "useBlack"), 1);
		glBindVertexArray(graphVAO);
		glDrawArrays(GL_LINE_STRIP, 0, 2880);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void createShader(unsigned int *shader, const char** shaderSource, GLenum shaderType) {
	*shader = glCreateShader(shaderType);

	glShaderSource(*shader, 1, shaderSource, NULL);
	glCompileShader(*shader);
}

void checkShaderSucess(unsigned int shader) {
	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
