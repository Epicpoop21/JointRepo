#include "Game.h"

Game::Game() 
{
	SetupContext();
	CreateWindow();
	CheckGladInit();
	glViewport(0, 0, 1920, 1080);

	shader = Shader("Rendering/VertexShader.s", "Rendering/FragmentShader.s");
}

Game::~Game()
{
}

int Game::StartUpdateLoop()
{
	vertices = { 0.0f,      0.0f,      0.0f,
			     0.0f,      1080.0f,   0.0f,
				 1920.0f,   0.0f,      0.0f,
				 1920.0f,   1090.0f,   0.0f};

	indices = { 0,  1,  2,
				1,  2,  3};

	VertexArray va;
	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	VertexBuffer vb(vertices.data(), vertices.size() * sizeof(float));
	IndexBuffer ib(indices.data(), indices.size() * sizeof(unsigned int));
	va.AddBuffer(vbl, vb);

	ParticleManager pm(shader);
	pm.SetupShader();

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);

	shader.Use();
	shader.SetMat4f("model", model);
	shader.SetMat4f("view", view);
	shader.SetMat4f("projection", projection);

	shader.SetVec3f("colour", 1.0f, 0.3f, 0.2f);


	
	while (!glfwWindowShouldClose(window)) {
		ProcessInput();

		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.Use();
		pm.Render();
		va.Bind();
		ib.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
	window = glfwCreateWindow(1920, 1080, "Particle Simulation", glfwGetPrimaryMonitor(), NULL);
	if (window == NULL) {
		std::cout << "FAILED TO INITIALISE WINDOW.\n";
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
}



