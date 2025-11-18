#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../util/Input.h"
#include "Shader.h"

class CubeRenderer;

#define screenY 1080.0f
#define screenX 1920.0f

class Camera {
public:
	Camera();
	~Camera();

	static Camera* GetInstance();

	static void Update();
	static void mouse_callback(GLFWwindow* window, double xPos, double yPos);
	static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
	static void MoveCamera();
	static void ScrollCamera();
	 
	static void Forward();
	static void Backward();
	static void Left();
	static void Right();

	static void BreakBlock();
private:

public:
	inline static glm::mat4 view = glm::mat4(1.0f);
	inline static glm::mat4 projection = glm::mat4(1.0f);
	inline static float cameraSpeed = 100.0f;

	inline static glm::vec3 cameraPos;
	inline static glm::vec3 cameraFront;
	inline static glm::vec3 cameraUp;

	inline static glm::vec2 camChunk;
private:
	inline static std::unique_ptr<Camera> s_Instance;
	  
	inline static float deltaTime = 0.0f;
	inline static float lastFrame = 0.0f;
	  
	inline static float yaw = -90.0f;
	inline static float pitch = 0.0f;
	inline static float fov = 45.0f;
	  
	inline static float yOffset;
	inline static double xPos, yPos;
	  
	inline static float lastX = screenX / 2, lastY = screenY / 2;
	inline static bool firstMouse = false;
	 
	inline static Input* input;
	inline static CubeRenderer* cr;
};