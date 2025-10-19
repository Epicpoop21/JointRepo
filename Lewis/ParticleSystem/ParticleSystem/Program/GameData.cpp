#include "GameData.h"

GameData::GameData() : startTime(time(NULL)), elapasedTime(0)
{
	eventHandler = EventHandler::GetInstance();
	paused = true;
	polyframe = false;
	eventHandler->GameEventDispatcher.AddListener(GameEvents::PauseToggle,
		std::bind(&GameData::InvertPause, this, std::placeholders::_1));

	eventHandler->GameEventDispatcher.AddListener(GameEvents::PolyframeToggle,
		std::bind(&GameData::PolyframeToggle, this, std::placeholders::_1));
}

GameData::~GameData()
{
}

void GameData::Update()
{
	elapasedTime = glfwGetTime() - startTime;
}

void GameData::InvertPause(const Event<GameEvents>& event)
{
	paused = !paused;
}

void GameData::PolyframeToggle(const Event<GameEvents>& event)
{
	polyframe = !polyframe;
	if (polyframe == true) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}