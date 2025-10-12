#pragma once
#include "../Renderer/Renderer.h"
#include "GameData.h"
#include <string>
#include "ball.h"
#include "Paddle.h"

class Game {
public:
	Game();
	~Game();

	void AddGameObjects(Ball* ball, Paddle* leftPaddle, Paddle* rightPaddle);
	void Update();

	void CheckCollisions();
private:
	GLFWwindow* CreateWindow(int width, int height, const char* title);
	int gladInit();
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
public:
	Shader shader;
	GLFWwindow* window;
	Renderer renderer;
	EventHandler* eventHandler = EventHandler::GetInstance();
	GameData data;

	Ball* ball;
	Paddle* leftPaddle;
	Paddle* rightPaddle;
private:

};
