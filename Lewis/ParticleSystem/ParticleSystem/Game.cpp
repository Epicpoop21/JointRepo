#include "Game.h"

Game::Game()
{
	SetupContext();
	CreateWindow();
	CheckGladInit();
	glViewport(0, 0, 1920, 1080);
	StartUpdateLoop();
}

Game::~Game()
{
}

int Game::StartUpdateLoop()
{
	while (!glfwWindowShouldClose(window)) {
		ProcessInput();
		glfwSwapBuffers(window);
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	}
	glfwTerminate();
	return 1;
}

void Game::ProcessInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}




void Game::SetupContext()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Game::CheckGladInit()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED TO INITIALISE GLAD. \n";
	}
}

void Game::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Game::CreateWindow()
{
	window = glfwCreateWindow(1920, 1080, "Particle Simulation", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL) {
		std::cout << "FAILED TO INITIALISE WINDOW.\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}



