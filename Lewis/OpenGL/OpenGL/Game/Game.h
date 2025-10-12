#pragma once
#include "../Renderer/Renderer.h"
#include "GameData.h"
#include "Bird.h"
#include "Tower.h"
#include <string>

class Game {
public:
	Game();
	~Game();
	void Update();
private:
	GLFWwindow* CreateWindow(int width, int height, const char* title);
	int gladInit();
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
	void InitObjects();
	void SpawnTower(const Event<GameEvents>& event);
	void ResetGame(const Event<GameEvents>& event);
	void MoveTowers();
	void CheckCollisions();
public:
	Shader shader;
	GLFWwindow* window;
	Renderer renderer;
	EventHandler* eventHandler = EventHandler::GetInstance();
	GameData data;

	Bird* bird;
private:
	std::vector<Tower*> towers;
};
