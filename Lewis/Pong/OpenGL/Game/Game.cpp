#include "Game.h"
#include <iostream>

Game::Game() 
{
	glfwInit();
	window = CreateWindow(1920, 1080, "Learn OpenLG");
	gladInit();
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glViewport(0, 0, 1920, 1080); 
	shader = Shader("vertexShader.vs", "fragmentShader.fs");
	renderer = Renderer(shader);
}

Game::~Game()
{

}

void Game::AddGameObjects(Ball* ball, Paddle* leftPaddle, Paddle* rightPaddle)
{
	this->ball = ball;
	this->leftPaddle = leftPaddle;
	this->rightPaddle = rightPaddle;
}

void Game::Update()
{

}

void Game::CheckCollisions()
{
	float ballCentreY = ball->ballLayout.centre.y;
	float ballCentreX = ball->ballLayout.centre.x;
	float ballRadius = ball->ballLayout.radius;

	if (ballCentreX + ballRadius > 1840.0f && (ballCentreY + ballRadius < rightPaddle->paddleLayout->centre.y + 100.0f && ballCentreY - ballRadius > rightPaddle->paddleLayout->centre.y - 100.0f)) {
		ball->ReflectPaddle();
		eventHandler->FireGameEvent(GameEvents::Score);
	}

	if (ballCentreX - ballRadius < 80.0f && (ballCentreY + ballRadius < leftPaddle->paddleLayout->centre.y + 100.0f && ballCentreY - ballRadius > leftPaddle->paddleLayout->centre.y - 100.0f)) {
		ball->ReflectPaddle();
		eventHandler->FireGameEvent(GameEvents::Score);
	}
}

GLFWwindow* Game::CreateWindow(int width, int height, const char* title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (window == NULL) {
		std::cout << "Failed to create window \n";
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);
	return window;
}

int Game::gladInit() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD";
		return -1;
	}
	return 1;
}

void Game::FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

