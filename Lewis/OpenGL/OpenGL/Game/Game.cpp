#include "Game.h"
#include <iostream>

Game::Game() 
{
	glfwInit();
	window = CreateWindow(1920, 1080, "Learn OpenLG");
	gladInit();
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
	glViewport(0, 0, 1920, 1080); 

	eventHandler->GameEventDispatcher.AddListener(GameEvents::BuildTower,
		std::bind(&Game::SpawnTower, this, std::placeholders::_1));
	eventHandler->GameEventDispatcher.AddListener(GameEvents::Restart,
		std::bind(&Game::ResetGame, this, std::placeholders::_1));

	shader = Shader("vertexShader.vs", "fragmentShader.fs");
	renderer = Renderer(shader);
	InitObjects();
	eventHandler->FireGameEvent(GameEvents::BuildTower);
}

Game::~Game()
{

}

void Game::Update()
{
	data.UpdateTime();
	if (!data.paused) {
		bird->Fall();
		MoveTowers();
		CheckCollisions();
	}

	for (auto& tower : towers) {
		renderer.RenderRectangle(tower->upperTower);
		renderer.RenderRectangle(tower->lowerTower);
	}
}

void Game::InitObjects()
{
	RenderLayout circle = renderer.CreateCircle(100.0f, 540.0f, 30.0f);
	bird = new Bird(std::move(circle));
}

void Game::SpawnTower(const Event<GameEvents>& event)
{
	if (!data.paused) {
		RenderLayout upper = renderer.CreateRectangle(xyCoord{ 2100.0f, 1140.0f }, 100.0f, 960.0f);
		RenderLayout lower = renderer.CreateRectangle(xyCoord{ 2100.0f, -60.0f }, 100.0f, 960.0f);

		towers.push_back(new Tower(std::move(upper), std::move(lower)));
	}
}

void Game::ResetGame(const Event<GameEvents>& event)
{
	bird->Die();
	eventHandler->FireGameEvent(GameEvents::PauseToggle);
	for (Tower* tower : towers) {
		delete tower;
	}
	towers.clear();
}

void Game::MoveTowers() {
	for (auto& tower : towers) {
		tower->upperTower.centre.x -= 4.5f;
		tower->lowerTower.centre.x -= 4.5f;
		tower->upperTower.modelMatrix = glm::translate(tower->upperTower.modelMatrix, glm::vec3(-4.5f, 0.0f, 0.0f));
		tower->lowerTower.modelMatrix = glm::translate(tower->lowerTower.modelMatrix, glm::vec3(-4.5f, 0.0f, 0.0f));
	}
}

void Game::CheckCollisions()
{
	float radius = bird->layout.radius;
	float maxY = bird->layout.centre.y + radius;
	float minY = bird->layout.centre.y - radius;
	float maxX = bird->layout.centre.x + radius;
	float minX = bird->layout.centre.x - radius;

	for (auto it = towers.begin(); it != towers.end();) {
		Tower* tower = *it;
		//std::cout << "RIGHT MOST X COORD IS: " << tower->upperTower.centre.x << " AND MAX X IS: " << maxX << "\n";

		if (tower->upperTower.centre.x + 50.0f < 0.0f) {
			delete tower;
			it = towers.erase(it);
			continue;
		}

		if (tower->upperTower.centre.x - 50.0f < maxX && tower->upperTower.centre.x + 50.0f > minX) {
			if (tower->bottomTowerTopCoord > minY || tower->topTowerBottomCoord < maxY) {
				eventHandler->FireGameEvent(GameEvents::Restart);
				break;
				//glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			}
		}
		++it;
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

