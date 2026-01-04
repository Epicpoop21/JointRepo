#include "InputTracker.h"

InputTracker::InputTracker(int side) {
	if (side == 0) {
		keyDownMap[GLFW_KEY_W] = false;
		keyDownMap[GLFW_KEY_S] = false;
	}
	else if (side == 1) {
		keyDownMap[GLFW_KEY_UP] = false;
		keyDownMap[GLFW_KEY_DOWN] = false;
	}
}

InputTracker::~InputTracker() {

}

void InputTracker::KeyPressed(int key, int action) {
	if (action == GLFW_PRESS) {
		keyDownMap[key] = true;
	}
	else if (action == GLFW_RELEASE) {
		keyDownMap[key] = false;
	}
}