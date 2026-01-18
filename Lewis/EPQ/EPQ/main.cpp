#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void framebuffer_resize_callback(GLFWwindow* window, int height, int width);
void key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() {
	glfwInit();
	//Telling GLFW what OpenGL version I want to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Create a window size 1920x1080. If the function returns nullptr, the function has failed
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Particle System", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "ERROR CREATING WINDOW\n";
		glfwTerminate();
		return -1;
	}
	//Makes the window current on the calling thread
	glfwMakeContextCurrent(window);

	//Load all OpenGL functions from the OS specific location specified by glfwGetProcAddress
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD\n";
		return -1;
	}


	//Specify the actual area on the window to render to
	glViewport(0, 0, 1920, 1080);
	//Gives GLFW a function to run if the size of the window is changed
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	glfwSetKeyCallback(window, key_input_callback);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		//Causes input and window related callbacks to be run
		glfwPollEvents();
	}
	glfwTerminate();

	return 1;
}

void key_input_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, 1);
	}
}

void framebuffer_resize_callback(GLFWwindow* window, int height, int width) {
	glViewport(0, 0, width, height);
}