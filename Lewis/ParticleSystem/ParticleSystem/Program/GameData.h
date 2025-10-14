#pragma once

#include <ctime>

#include "../Rendering/Renderer.h"

class GameData {
public:
	GameData();
	~GameData();
private:

public:
	int elapasedTime;
	time_t startTime;
private:

};