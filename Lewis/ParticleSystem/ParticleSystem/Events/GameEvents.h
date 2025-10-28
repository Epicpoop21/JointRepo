#pragma once
#include "Event.h"

enum class GameEvents {
	PauseToggle,
	PolyframeToggle,
	MouseIsDown, 
	MouseIsUp
};

class PauseToggleEvent : public Event<GameEvents> {
public:
	PauseToggleEvent() : Event<GameEvents>(GameEvents::PauseToggle, "PauseToggle") {}
	virtual ~PauseToggleEvent() {}
};

class PolyframeToggleEvent : public Event<GameEvents> {
public:
	PolyframeToggleEvent() : Event<GameEvents>(GameEvents::PolyframeToggle, "PolyframeToggle") {}
	virtual ~PolyframeToggleEvent() {}
};

class MouseIsDownEvent : public Event<GameEvents> {
public:
	MouseIsDownEvent() : Event<GameEvents>(GameEvents::MouseIsDown, "MouseIsDown") {}
	virtual ~MouseIsDownEvent() {}
};

class MouseIsUpEvent : public Event<GameEvents> {
public:
	MouseIsUpEvent() : Event<GameEvents>(GameEvents::MouseIsUp, "MouseIsUp") {}
	virtual ~MouseIsUpEvent() {}
};