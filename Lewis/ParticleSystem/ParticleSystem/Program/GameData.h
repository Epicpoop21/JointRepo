#pragma once

#include <ctime>

#include "../Rendering/Renderer.h"
#include "../Events/EventHeader.h"

class GameData {
public:
	GameData();
	~GameData();

	void Update();
private:
	void InvertPause(const Event<GameEvents>& event);
	void PolyframeToggle(const Event<GameEvents>& event);
public:
	int elapasedTime;
	time_t startTime;
	bool paused;
	bool polyframe;
private:
	EventHandler* eventHandler;
};