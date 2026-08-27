#pragma once

#include "GameData.h"
#include "ParticleManager.h"

#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

class GUIManager
{
public:
	GUIManager();
	~GUIManager();

	void Setup(GLFWwindow* window, GameData* gameData);

	void Render();
private:
	ImGuiWindowFlags windowFlags;

	GLFWwindow* window;
	GameData* gameData;

	int count;
public:

private:

};

