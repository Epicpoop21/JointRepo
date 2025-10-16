#pragma once
#include <iostream>
#include <vector>

#include "../Rendering/Renderer.h"
#include "ParticleManager.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Shader shader;
};

