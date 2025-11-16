#include "Input.h"

std::unique_ptr<Input> Input::s_Instance = nullptr;
Input* Input::GetInstance() {
	if (!s_Instance) {
		s_Instance = std::make_unique<Input>();
	}
	return s_Instance.get();
}

void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{	
	keyStateMap[key] = ActionToBool(action);
}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	keyStateMap[button] = ActionToBool(action);
}

bool Input::ActionToBool(GLenum action)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		return true;
	}
	else {
		return false;
	}
}

/*
if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		if (!polyframe) {
			polyframe = true;
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			polyframe = false;
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		cam.Forward();
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		cam.Backward();
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		cam.Left();
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		cam.Right();
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS)
		cam.cameraSpeed = 0.1f;
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE)
		cam.cameraSpeed = 0.05f;
*/