#include <iostream>
#include <map>
#include "Renderer/Renderer.h"
#include "Events/EventHandler.h"

#include "Game/Game.h"
#include "Game/GameData.h"
#include "Game/ball.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void ProcessInput(GLFWwindow* window, Game& game, std::map<int, bool>* keyMap);

int main() {
	Game game;
	Shader shader = game.shader;
	GLFWwindow* window = game.window;
	Renderer renderer = game.renderer;

	RenderLayout rectangle1 = renderer.CreateRectangle(50.0f, 540.0f, 30.0f, 200.0f);
	RenderLayout rectangle2 = renderer.CreateRectangle(1870.0f, 540.0f, 30.0f, 200.0f);
	RenderLayout circle = renderer.CreateCircle(960.0f, 540.0f, 20.0f); 

	

	glm::mat4 projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1000.0f, 1000.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 ballModel = glm::mat4(1.0f);


	Ball ball(circle);
	Paddle lPaddle(&rectangle1);
	Paddle rPaddle(&rectangle2);

	game.AddGameObjects(&ball, &lPaddle, &rPaddle);

	std::map<int, bool> keyMap;
	keyMap[GLFW_KEY_SPACE] = false;
	keyMap[GLFW_KEY_P] = false;
	while (!glfwWindowShouldClose(window)) {
		//Processes input
		ProcessInput(window, game, &keyMap);

		//Rendering
		glClearColor(0.3f, 0.5f, 0.6f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.SetFloatVec4("colorValue", 0.5f, 0.2f, 0.7f, 1.0f);


		shader.Use();
		shader.SetFloatMat4("view", 1, GL_FALSE, glm::value_ptr(view));
		shader.SetFloatMat4("projection", 1, GL_FALSE, glm::value_ptr(projection));

		shader.SetFloatMat4("model", 1, GL_FALSE, glm::value_ptr(lPaddle.modelMatrix));
		renderer.RenderRectangle(rectangle1);

		shader.SetFloatMat4("model", 1, GL_FALSE, glm::value_ptr(rPaddle.modelMatrix));
		renderer.RenderRectangle(rectangle2);

		shader.SetFloatMat4("model", 1, GL_FALSE, glm::value_ptr(ballModel));
		renderer.RenderCircle(circle);
		ball.Move();
		game.CheckCollisions();

		std::cout << game.data.score << "\n";

		//Check events and swap buffer
		glfwSwapBuffers(window); 
		glfwPollEvents();
	}
	glfwTerminate();

	return 1;
}

void ProcessInput(GLFWwindow* window, Game& game, std::map<int, bool> *keyMap) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		game.leftPaddle->Move(1);
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		game.leftPaddle->Move(0);
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		game.rightPaddle->Move(1);
	}

	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		game.rightPaddle->Move(0);
	}

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		if (keyMap->at(GLFW_KEY_SPACE) == false) {
			keyMap->at(GLFW_KEY_SPACE) = true;
			std::cout << "Clicked space \n";
			game.eventHandler->FireGameEvent(GameEvents::PauseToggle);
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
	
}

