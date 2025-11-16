#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../util/Input.h"
#include "Shader.h"

#define screenY 1080.0f
#define screenX 1920.0f

class Camera {
public:
	Camera();
	~Camera();

	void Update();
	static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
	static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
	void MoveCamera();
	void ScrollCamera();

	void Forward();
	void Backward();
	void Left();
	void Right();
private:

public:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);
	float cameraSpeed = 2.0f;
private:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float yaw = -90.0f;
	float pitch = 0.0f;
	float fov = 45.0f;

	inline static float yOffset;
	inline static double xPos, yPos;

	float lastX = screenX / 2, lastY = screenY / 2;
	bool firstMouse = false;

	Input* input;
};