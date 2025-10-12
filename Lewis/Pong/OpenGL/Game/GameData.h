#pragma once
#include <ctime>
#include "../Events/EventHeader.h"
#include "../Renderer/Renderer.h"

class GameData {
public:
	GameData();
	~GameData();

	bool GetPausedState();
	void InvertPause(const Event<GameEvents>& event);
	void InvertPolyframeMode(const Event<GameEvents>& event);
	void IncrementScore(const Event<GameEvents>& event);
	void ResetScore(const Event<GameEvents>& event);
private:

public:
	int score;
	time_t startTime;
	time_t currentTime;
	bool paused;
	bool polyframeMode;
	EventHandler* eventHandler;
private:

};
