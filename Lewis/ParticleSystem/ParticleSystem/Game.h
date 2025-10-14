#pragma once
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Game
{
public:
	Game();
	~Game();
	int StartUpdateLoop();
private:
	void SetupContext();
	void CreateWindow();
	void CheckGladInit();
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void ProcessInput();
public:

private:
	GLFWwindow* window;
};

