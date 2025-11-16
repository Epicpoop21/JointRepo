#include "Camera.h"

Camera::Camera(Shader& shader) : shader(shader)
{
	fov = 45.0f;

	cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraFront);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	cameraUp = glm::cross(cameraDirection, cameraRight);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	MoveCamera();

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	shader.SetMat4f("view", view);
	projection = glm::perspective(glm::radians(fov), screenX / screenY, 0.1f, 500.0f);
	shader.SetMat4f("projection", projection);
}

void Camera::mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	xPos = xPos;
	yPos = yPos;
}

void Camera::scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	yOffset = yOffset;
}

void Camera::ScrollCamera() {
	fov -= (float)yOffset;
	if (fov < 1.0f) fov = 1.0f;
	if (fov > 45.0f) fov = 45.0f;
}

void Camera::MoveCamera() 
{
	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;
	lastX = xPos;
	lastY = yPos;

	const float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 98.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	direction.y = glm::sin(glm::radians(pitch));

	cameraFront = glm::normalize(direction);
}

void Camera::Forward()
{
	cameraPos += cameraSpeed * cameraFront;
}

void Camera::Backward()
{
	cameraPos -= cameraSpeed * cameraFront;
}

void Camera::Left()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::Right()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}