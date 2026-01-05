#include <iostream>
#include <string>

#include "game/Game.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "UDPHandler.h"

int main() {
	UDPHandler udpHandler("172.30.202.136", 55555);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Pong", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "ERROR CREATING WINDOW\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED TO INITIALISE GLAD\n";
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 1920, 1080);

	Game game(window, &udpHandler);
	udpHandler.~UDPHandler();
	return 1;
}