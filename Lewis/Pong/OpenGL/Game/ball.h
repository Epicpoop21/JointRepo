#pragma once
#include "../Renderer/Renderer.h"
#include <functional>
#include "../Events/EventHeader.h"

class Ball {
public:
	Ball(RenderLayout& ballLayout);
	~Ball();

	void Move();
	void ReflectPaddle();
private:
	void Pause(const Event<GameEvents>& event);
public:
	int velocity;
	xyCoord direction;
	bool paused;
	RenderLayout& ballLayout;
private:
	EventHandler* eventHandler = EventHandler::GetInstance();
};