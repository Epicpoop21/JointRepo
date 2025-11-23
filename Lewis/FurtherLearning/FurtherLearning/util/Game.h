#pragma once

#include <optional>

#include "Input.h"
#include "../rendering/RenderingHeaders.h"

class Game
{
public:
	Game();
	~Game();
	void Update();

private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
public:

private:
	GLFWwindow* window;
	Shader worldShader;
	Shader UIShader;
	Input input;
	CubeRenderer* cr;
	Camera* cam;
	UI* ui;

	inline static bool polyframe;
};

