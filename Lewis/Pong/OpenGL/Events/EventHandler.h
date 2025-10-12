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

#define AddGameEventListener(eventType, func, arg) EventHandler::GetInstance()->GameEventDispatcher.AddListener(eventType, std::bind(&func, arg, std::placeholders::_1));

#define RemoveGameEventListener(eventType, listenerId) EventHandler::GetInstance()->GameEventDispatcher.RemoveListener(type, listenerID);
