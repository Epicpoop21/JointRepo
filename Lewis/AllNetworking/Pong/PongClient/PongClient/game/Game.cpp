#include "Game.h"

float Game::deltaTime = 0.0f;
float Game::lastTime = 0.0f;
UDPHandler* Game::udpHandler = nullptr;

Game::Game(GLFWwindow* window, UDPHandler* udpHandler)
	: lPaddle(0, glm::vec2(80.0f, 720.0f)),
	rPaddle(1, glm::vec2(2500.0f, 720.0f)),
	window(window),
	ball(glm::vec2(1280, 720))
{
	Game::udpHandler = udpHandler;
	udpHandler->SetGame(this);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keypress_callback);

	GameLoop();
}

Game::~Game()
{
}

void Game::GameLoop()
{
	while (!glfwWindowShouldClose(window)) {
		udpHandler->GetDataFromServer();
		CalculateDeltaTime();
		glClearColor(0.09f, 0.15f, 0.13f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		renderer.Render(lPaddle.rd, 6);
		renderer.Render(rPaddle.rd, 6);
		renderer.Render(ball.rd, 6);

		//lPaddle.Move(glm::vec2(0.0f, 1.0f) * 50.0f * deltaTime);
		
		glfwPollEvents();
		glfwSwapBuffers(window); 
	}
	glfwTerminate();
}

void Game::CalculateDeltaTime()
{
	deltaTime = glfwGetTime() - lastTime;
	lastTime = glfwGetTime();
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Game::keypress_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (action != GLFW_REPEAT) {
		udpHandler->SendInput(action, key);
	}
}