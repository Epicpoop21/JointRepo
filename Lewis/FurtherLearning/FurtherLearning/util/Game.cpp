#include "Game.h"

Game::Game()
{
	std::cout << "Works to here \n";
	polyframe = false;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenX, screenY, "Further learning OpenGL", NULL, NULL);
	if (!window) {
		std::cout << "ERROR CREATING WINDOW. EXITING. \n";
		glfwTerminate();
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, Input::key_callback);
	glfwSetMouseButtonCallback(window, Input::mouse_button_callback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, Camera::mouse_callback);
	glfwSetScrollCallback(window, Camera::scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "FAILED TO INITIALISE GLAD. \n";
	}

	worldShader = Shader("rendering/Shaders/WorldVS.s", "rendering/Shaders/WorldFS.s");
	UIShader = Shader("rendering/Shaders/UIVS.s", "rendering/Shaders/UIFS.s");

	cr = CubeRenderer::GetInstance();
	cr->AddShader(&worldShader);
	cam = Camera::GetInstance();
	ui = new UI(&UIShader);

	glViewport(0, 0, screenX, screenY);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_CCW);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Game::~Game()
{
}

void Game::Update()
{
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.7f, 0.7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cam->Update();
		cr->Render();
		ui->Update();

		if (input.keyStateMap[GLFW_KEY_ESCAPE]) glfwSetWindowShouldClose(window, true);
		if (input.keyStateMap[GLFW_MOUSE_BUTTON_1]) cr->RemoveBlock();
		if (input.keyStateMap[GLFW_KEY_P] && polyframe == false) {
			polyframe = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		} else if (input.keyStateMap[GLFW_KEY_P] && polyframe == true) {
			polyframe = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
}

void Game::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}