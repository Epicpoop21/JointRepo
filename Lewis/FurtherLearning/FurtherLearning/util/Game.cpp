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

	shader = Shader("rendering/VertexShader.s", "rendering/FragmentShader.s");
	cr.emplace();

	glViewport(0, 0, screenX, screenY);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_CCW);
}

Game::~Game()
{
}

void Game::Update()
{
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader.Use();
		shader.SetInt("textureImage", 0);
		cam.Update();
		cr->Render();
		shader.SetMat4f("view", cam.view);
		shader.SetMat4f("projection", cam.projection);
		if (input.keyStateMap[GLFW_KEY_ESCAPE]) glfwSetWindowShouldClose(window, true);
		if (input.keyStateMap[GLFW_MOUSE_BUTTON_1]) std::cout << "Left click \n";
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