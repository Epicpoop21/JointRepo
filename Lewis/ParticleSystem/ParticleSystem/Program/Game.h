#pragma once
#include <iostream>
#include <vector>

#include "../Rendering/Renderer.h"
#include "../Events/EventHeader.h"

#include "ParticleManager.h"
#include "GameData.h"

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
	GameData data;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	Shader shader;
	std::unordered_map<GLenum, bool> keyMap;
	EventHandler* eventHandler;
};

