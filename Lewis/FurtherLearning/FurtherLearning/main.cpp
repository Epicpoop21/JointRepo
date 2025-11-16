#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "rendering/Shader.h"
#include "rendering/VertexBuffer.h"
#include "rendering/IndexBuffer.h"
#include "rendering/VertexArray.h"
#include "rendering/VertexBufferLayout.h"
#include "rendering/Camera.h"

#include "rendering/CubeRenderer.h"

#include <iostream>

#define screenY 600.0f
#define screenX 800.0f

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window, Camera& cam);

bool polyframe = false;
CubeRenderer cr;

int main() {
	std::cout << "Hello world\n";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(screenX, screenY, "Further learning OpenGL", NULL, NULL);
	if (!window) {
		std::cout << "ERROR CREATING WINDOW. EXITING. \n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, Camera::mouse_callback);
	glfwSetScrollCallback(window, Camera::scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED TO INITIALISE GLAD. \n";
	}
	glViewport(0, 0, screenX, screenY);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	Shader shader("./rendering/VertexShader.s", "./rendering/FragmentShader.s");
	Camera cam(shader);

	/*
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

	VertexBuffer vb(vertices, sizeof(vertices));
	IndexBuffer ib(indices, sizeof(indices));
	VertexBufferLayout vbl;
	VertexArray va; 

	vbl.Push<float>(3);
	vbl.Push<float>(3);
	va.AddBuffer(vb, vbl);  */


	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window, cam);

		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();

		cr.Render();
		cam.Update();
		
		/*va.Bind();
		ib.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, NULL); */

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

void ProcessInput(GLFWwindow* window, Camera& cam)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		if (!polyframe) {
			polyframe = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			polyframe = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.Forward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.Backward();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.Left();
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.Right();
}
