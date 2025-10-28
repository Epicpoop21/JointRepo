#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/Shader.h"
#include "rendering/VertexBuffer.h"
#include "rendering/IndexBuffer.h"
#include "rendering/VertexArray.h"
#include "rendering/VertexBufferLayout.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

float cameraSpeed = 0.1f;

int main() {
	std::cout << "Hello world\n";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Further learning OpenGL", NULL, NULL);
	if (!window) {
		std::cout << "ERROR CREATING WINDOW. EXITING. \n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED TO INITIALISE GLAD. \n";
	}
	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);

	Shader shader("./rendering/VertexShader.s", "./rendering/FragmentShader.s");

	float vertices[] = {
		//FRONT FACE
		-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,

		 //LEFT FACE
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

		//RIGHT FACE
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f
	};

	unsigned int indices[] = {
		//FRONT FACE
		0, 1, 2,
		1, 2, 3,

		//LEFT FACE
		0, 1, 4,
		0, 5, 4,

		//RIGHT FACE
		2, 3, 6,
		2, 6, 7,

		//TOP FACE
		1, 3, 4,
		3, 4, 6,

		//BOTTOM FACE
		0, 2, 5,
		2, 5, 7,

		//BACK FACE
		5, 4, 6,
		5, 6, 7
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	VertexBuffer vb(vertices, sizeof(vertices));
	IndexBuffer ib(indices, sizeof(indices));
	VertexBufferLayout vbl;
	VertexArray va;

	vbl.Push<float>(3);
	vbl.Push<float>(3);
	va.AddBuffer(vb, vbl);

	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraFront);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

	const float radius = 7.0f;
	float camX = glm::sin(glfwGetTime()) * radius;
	float camZ = glm::cos(glfwGetTime()) * radius;

	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window);

		float camX = glm::sin(glfwGetTime()) * radius;
		float camZ = glm::cos(glfwGetTime()) * radius;
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		//model = glm::rotate(model, (float)glfwGetTime() * glm::radians(5.0f), glm::vec3(0.5f, 1.0f, 0.0f));

		shader.SetMat4f("view", view);
		shader.SetMat4f("projection", projection);

		va.Bind();
		ib.Bind();
		for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float tilt = 20.0f * i;
			model = glm::rotate(model, glm::radians(tilt), glm::vec3(1.0f, 1.0f, 0.0f));
			shader.SetMat4f("model", model);
			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
			
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
