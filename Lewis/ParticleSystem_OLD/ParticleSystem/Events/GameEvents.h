#pragma once
#include "Event.h"

enum class GameEvents {
	PauseToggle,
	PolyframeToggle,
	MouseIsDown
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