#pragma once
#include <iostream>
#include <string>

#include "../rendering/Renderer.h"
#include "Paddle.h"
#include "Ball.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "../UDPHandler.h"

class Game
{
public:
	Game(GLFWwindow* window, UDPHandler* udpHandler);
	~Game();
private:
	void GameLoop();
	static void CalculateDeltaTime();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void keypress_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
public:
	static float deltaTime;
	Paddle lPaddle;
	Paddle rPaddle;
	Ball ball;
private:
	GLFWwindow* window;
	Renderer renderer;
	static float lastTime;
	static UDPHandler* udpHandler;
};

