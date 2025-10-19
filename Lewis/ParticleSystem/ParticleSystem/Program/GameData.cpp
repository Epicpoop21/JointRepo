#include "GameData.h"

GameData::GameData() : startTime(time(NULL)), elapasedTime(0), mousePos(0.0f)
{
	screenX = 0.0f;
	screenY = 0.0f;
	eventHandler = EventHandler::GetInstance();
	paused = true;
	polyframe = false;
	eventHandler->GameEventDispatcher.AddListener(GameEvents::PauseToggle,
		std::bind(&GameData::InvertPause, this, std::placeholders::_1));

	eventHandler->GameEventDispatcher.AddListener(GameEvents::PolyframeToggle,
		std::bind(&GameData::PolyframeToggle, this, std::placeholders::_1));

	eventHandler->GameEventDispatcher.AddListener(GameEvents::MouseIsDown,
		std::bind(&GameData::Click, this, std::placeholders::_1));
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

void GameData::Click(const Event<GameEvents>& event)
{
	double mousePosX, mousePosY;
	glfwGetCursorPos(glfwGetCurrentContext(), &mousePosX, &mousePosY);
	mousePos.x = mousePosX;
	mousePos.y = -mousePosY + screenY;
}
