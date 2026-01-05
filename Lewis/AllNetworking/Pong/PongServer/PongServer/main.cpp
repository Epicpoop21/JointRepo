#include <iostream>
#include <string>
#include "UDPHandler.h"

#include "./Objects/Object.h"
#include "./Objects/Ball.h"
#include "./Objects/Paddle.h"

#include "GLFW/glfw3.h"

int main() {
	glfwInit();
	Paddle lPaddle(glm::vec2(80.0f, 540.0f));
	Paddle rPaddle(glm::vec2(1840.0f, 540.0f));
	Ball ball(glm::vec2(960.0f, 540.0f));

	UDPHandler handler("0.0.0.0", 55555);

	glm::vec2 moveUpVec = glm::vec2(0.0f, 10.0f);
	glm::vec2 moveDownVec = glm::vec2(0.0f, -10.0f);

	while (true) {
		if (handler.userManager.ball->Move(handler.userManager.ball->currentVelocity)) handler.BroadcastMovement({ 2, handler.userManager.ball->centre });
		ball.CheckCollisions(lPaddle.centre, rPaddle.centre);

		auto it = handler.userManager.userIdMap.find(0);
		if (it != handler.userManager.userIdMap.end()) {
			if (it->second.inputTracker.keyDownMap[GLFW_KEY_W]) {
				if (handler.userManager.lPaddle->Move(moveUpVec)) {
					handler.BroadcastMovement({ 0, moveUpVec });
				}
			}
			else if (it->second.inputTracker.keyDownMap[GLFW_KEY_S]) {
				if (handler.userManager.lPaddle->Move(moveDownVec)) {
					handler.BroadcastMovement({ 0, moveDownVec });
				}
			}
		}

		it = handler.userManager.userIdMap.find(1);
		if (it != handler.userManager.userIdMap.end()) {
			if (it->second.inputTracker.keyDownMap[GLFW_KEY_UP]) {
				if (handler.userManager.lPaddle->Move(moveUpVec)) {
					handler.BroadcastMovement({ 1, moveUpVec });
				}
			}
			else if (it->second.inputTracker.keyDownMap[GLFW_KEY_DOWN]) {
				if (handler.userManager.lPaddle->Move(moveDownVec)) {
					handler.BroadcastMovement({ 1, moveDownVec });
				}
			}
		}

		handler.GetDataInSocket();
	}

	return 1;
}