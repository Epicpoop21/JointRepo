#include "Game.h"
#include <thread>
Game::Game() 
{
	data = GameData();
	data.paused = false;
	data.screenX = 1920.0f;
	data.screenY = 1080.0f;
	SetupContext();
	CreateWindow();
	CheckGladInit();
	glViewport(0, 0, data.screenX, data.screenY);
	shader = Shader("Rendering/VertexShader.s", "Rendering/FragmentShader.s", nullptr);
	eventHandler = EventHandler::GetInstance();
}

Game::~Game()
{
}

int Game::StartUpdateLoop()
{
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::ortho(0.0f, data.screenX, 0.0f, data.screenY);

	shader.UseGraphics();
	shader.SetMat4f("model", model);
	shader.SetMat4f("view", view);
	shader.SetMat4f("projection", projection);

	shader.SetVec3f("colour", 1.0f, 0.3f, 0.2f);

	ParticleManager pm(shader, &data);
	pm.Setup();

	float lastTime = glfwGetTime();
	float deltaTime;

	keyMap[GLFW_KEY_SPACE] = false;
	keyMap[GLFW_KEY_P] = false;

	while (!glfwWindowShouldClose(window)) {

		ProcessInput();

		deltaTime = glfwGetTime() - lastTime;
		lastTime = glfwGetTime();

		glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.UseGraphics();

		if (!data.paused) {
			pm.Vibrate(deltaTime);
			//pm.CheckCollisions();
		}
		pm.Render();

		glfwSwapBuffers(window);
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

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !keyMap[GLFW_KEY_SPACE]) {
		keyMap[GLFW_KEY_SPACE] = true;
		eventHandler->FireGameEvent(GameEvents::PauseToggle);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE && keyMap[GLFW_KEY_SPACE]) {
		keyMap[GLFW_KEY_SPACE] = false;
	}

	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && !keyMap[GLFW_KEY_P]) {
		keyMap[GLFW_KEY_P] = true;
		eventHandler->FireGameEvent(GameEvents::PolyframeToggle);
	}
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE && keyMap[GLFW_KEY_P]) {
		keyMap[GLFW_KEY_P] = false;
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		EventHandler::GetInstance()->FireGameEvent(GameEvents::MouseIsDown);
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
	window = glfwCreateWindow(data.screenX, data.screenY, "Particle Simulation", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL) {
		std::cout << "FAILED TO INITIALISE WINDOW.\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}



