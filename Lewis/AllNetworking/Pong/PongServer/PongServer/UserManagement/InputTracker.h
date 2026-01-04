#pragma once

#include <map>

#include <GLFW/glfw3.h>

class InputTracker {
public:
	InputTracker(int side);
	~InputTracker();

	void KeyPressed(int key, int action);
private:

public:
	std::map<int, bool> keyDownMap;
private:

};