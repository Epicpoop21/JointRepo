#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Error creating window \n";
		glfwTerminate();
	}

	return 1;
}

