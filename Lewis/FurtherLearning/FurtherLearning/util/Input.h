#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <memory>
#include <iostream>

class Input
{
public:
	static Input* GetInstance();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
private:
	static bool ActionToBool(GLenum action);
public:
	inline static std::unordered_map<GLenum, bool> keyStateMap;
private:
	static std::unique_ptr<Input> s_Instance;
};

