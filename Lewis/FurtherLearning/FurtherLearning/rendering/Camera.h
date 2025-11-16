#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#define screenY 600.0f
#define screenX 800.0f

class Camera {
public:
	Camera(Shader& shader);
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

private:
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	Shader& shader;

	float cameraSpeed = 0.05f;
	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	float yaw = -90.0f;
	float pitch = 0.0f;
	float fov = 45.0f;
	static float yOffset;
	
	static double xPos, yPos;

	float lastX = screenX / 2, lastY = screenY / 2;
	bool firstMouse = false;
};