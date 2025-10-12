#include "GameData.h"
#include <iostream>

GameData::GameData()
	:paused(true), polyframeMode(true), score(0), buildingTower(false)
{
	time(&startTime);
	time(&currentTime);
	eventHandler = EventHandler::GetInstance();

	eventHandler->GameEventDispatcher.AddListener(GameEvents::PauseToggle,
		std::bind(&GameData::InvertPause, this, std::placeholders::_1));

	eventHandler->GameEventDispatcher.AddListener(GameEvents::PolyframeToggle,
		std::bind(&GameData::InvertPolyframeMode, this, std::placeholders::_1));

	eventHandler->GameEventDispatcher.AddListener(GameEvents::Score,
		std::bind(&GameData::IncrementScore, this, std::placeholders::_1));

	eventHandler->GameEventDispatcher.AddListener(GameEvents::Restart,
		std::bind(&GameData::ResetScore, this, std::placeholders::_1));
}

GameData::~GameData()
{

}

bool GameData::GetPausedState()
{
	return paused;
}

void GameData::InvertPause(const Event<GameEvents>& event)
{
	paused = !paused;
	std::cout << "State is: " << GetPausedState() << "\n";
}

void GameData::InvertPolyframeMode(const Event<GameEvents>& event)
{
	polyframeMode = !polyframeMode;
	std::cout << "Inverted polyframe mode \n";
	if (polyframeMode) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}

void GameData::IncrementScore(const Event<GameEvents>& event) {
	score++;
}

void GameData::ResetScore(const Event<GameEvents>& event) {
	score = 0;
}

void GameData::UpdateTime() {
	time(&currentTime);
	timeElapsed = currentTime - startTime;

	if (timeElapsed % 2 == 0 && buildingTower == false) {
		buildingTower = true;
		eventHandler->FireGameEvent(GameEvents::BuildTower);
	}
	else if (timeElapsed % 2 == 1 && buildingTower == true) {
		buildingTower = false;
	}
}