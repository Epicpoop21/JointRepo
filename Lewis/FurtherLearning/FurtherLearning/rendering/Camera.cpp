#include "Camera.h"
#include <math.h>

Camera::Camera() : input(Input::GetInstance())
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
	if (input->keyStateMap[GLFW_KEY_W]) Forward();
	if (input->keyStateMap[GLFW_KEY_D]) Right();
	if (input->keyStateMap[GLFW_KEY_S]) Backward();
	if (input->keyStateMap[GLFW_KEY_A]) Left();
	if (input->keyStateMap[GLFW_KEY_LEFT_SHIFT]) cameraSpeed = 4.0f;
	if (!input->keyStateMap[GLFW_KEY_LEFT_SHIFT]) cameraSpeed = 2.0f;

	MoveCamera();
	ScrollCamera();

	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//std::cout << std::round((1.f / deltaTime)) << std::endl;

	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	projection = glm::perspective(glm::radians(fov), screenX / screenY, 0.1f, 500.0f);
}

void Camera::mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	Camera::xPos = xPos;
	Camera::yPos = yPos;
}

void Camera::scroll_callback(GLFWwindow* window, double xOffset, double yOffset) {
	Camera::yOffset = yOffset;
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

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	glm::vec3 direction;
	direction.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	direction.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	direction.y = glm::sin(glm::radians(pitch));

	cameraFront = glm::normalize(direction);
}

void Camera::Forward()
{
	cameraPos += cameraSpeed * deltaTime * cameraFront;
}

void Camera::Backward()
{
	cameraPos -= cameraSpeed * deltaTime * cameraFront;
}

void Camera::Left()
{
	cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * deltaTime * cameraSpeed;
}

void Camera::Right()
{
	cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * deltaTime * cameraSpeed;
}