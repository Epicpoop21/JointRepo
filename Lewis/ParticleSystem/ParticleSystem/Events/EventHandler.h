#pragma once
#include <memory>

#include "Event.h"
#include "EventDispatcher.h"

#include "GameEvents.h"

class EventHandler {
public:
	EventHandler() : GameEventDispatcher() {}
	static EventHandler* GetInstance();

	EventDispatcher<GameEvents> GameEventDispatcher;

	void FireGameEvent(const Event<GameEvents>& event) {
		GameEventDispatcher.SendEvent(event);
	}

private:
	static std::unique_ptr<EventHandler> s_Instance;
};