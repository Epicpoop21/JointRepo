#include <iostream>
#include <map>
#include "Renderer/Renderer.h"
#include "Events/EventHandler.h"

#include "Game/Game.h"
#include "Game/GameData.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void ProcessInput(GLFWwindow* window, Game& game, std::map<int, bool>* keyMap);

int main() {
	Game game;
	Shader shader = game.shader;
	GLFWwindow* window = game.window;
	Renderer renderer = game.renderer;

	glm::mat4 projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1000.0f, 1000.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 ballModel = glm::mat4(1.0f);

	std::map<int, bool> keyMap;
	keyMap[GLFW_KEY_SPACE] = false;
	keyMap[GLFW_KEY_P] = false;
	keyMap[GLFW_KEY_C] = false;
	keyMap[GLFW_KEY_R] = false;
	glClearColor(0.3f, 0.5f, 0.6f, 0.0f);
	while (!glfwWindowShouldClose(window)) {
		//Processes input
		ProcessInput(window, game, &keyMap);

		//Rendering
		glClear(GL_COLOR_BUFFER_BIT);

		shader.SetFloatVec4("colorValue", 0.5f, 0.2f, 0.7f, 1.0f);


		shader.Use();
		shader.SetFloatMat4("view", 1, GL_FALSE, glm::value_ptr(view));
		shader.SetFloatMat4("projection", 1, GL_FALSE, glm::value_ptr(projection));

		shader.SetFloatMat4("model", 1, GL_FALSE, glm::value_ptr(ballModel));
		renderer.RenderCircle(game.bird->layout);

		game.Update();

		//std::cout << game.data.timeElapsed << "\n";

		//Check events and swap buffer
		glfwSwapBuffers(window); 
		glfwPollEvents();
	}
	glfwTerminate();

	return 1;
}

void ProcessInput(GLFWwindow* window, Game& game, std::map<int, bool> *keyMap) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (keyMap->at(GLFW_KEY_SPACE) == false) {
			keyMap->at(GLFW_KEY_SPACE) = true;
			game.bird->Jump();
		}
	} else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE) {
		if (keyMap->at(GLFW_KEY_SPACE) == true) {
			keyMap->at(GLFW_KEY_SPACE) = false;
		}
	}


	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
		if (keyMap->at(GLFW_KEY_P) == false) {
			keyMap->at(GLFW_KEY_P) = true;
			game.eventHandler->FireGameEvent(GameEvents::PolyframeToggle);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
		if (keyMap->at(GLFW_KEY_P) == true) {
			keyMap->at(GLFW_KEY_P) = false;
		}
	}
	
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		if (keyMap->at(GLFW_KEY_C) == false) {
			keyMap->at(GLFW_KEY_C) = true;
			game.eventHandler->FireGameEvent(GameEvents::PauseToggle);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
		if (keyMap->at(GLFW_KEY_C) == true) {
			keyMap->at(GLFW_KEY_C) = false;
		}
	}

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		if (keyMap->at(GLFW_KEY_R) == false) {
			keyMap->at(GLFW_KEY_R) = true;
			glClearColor(0.3f, 0.5f, 0.6f, 0.0f);
		}
	}
	else if (glfwGetKey(window, GLFW_KEY_R) == GLFW_RELEASE) {
		if (keyMap->at(GLFW_KEY_R) == true) {
			keyMap->at(GLFW_KEY_R) = false;
		}
	}
}

