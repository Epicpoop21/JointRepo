#pragma once
#include "Event.h"

enum class GameEvents {
	PauseToggle,
	Score,
	Restart,
	Finish,
	BuildTower,
	PolyframeToggle
};

class PauseToggleEvent : public Event<GameEvents> {
public:
	PauseToggleEvent() : Event<GameEvents>(GameEvents::PauseToggle, "PauseToggle") {}
	virtual ~PauseToggleEvent() {}
};

class ScoreEvent : public Event<GameEvents> {
public:
	ScoreEvent() : Event<GameEvents>(GameEvents::Score, "Score") {}
	virtual ~ScoreEvent() {}
};

class RestartEvent : public Event<GameEvents> {
public:
	RestartEvent() : Event<GameEvents>(GameEvents::Restart, "Restart") {}
	virtual ~RestartEvent() {}
};

class BuildTowerEvent : public Event<GameEvents> {
public:
	BuildTowerEvent() : Event<GameEvents>(GameEvents::BuildTower, "BuildTower") {}
	virtual ~BuildTowerEvent() {}
};

class PolyframeToggleEvent : public Event<GameEvents> {
public:
	PolyframeToggleEvent() : Event<GameEvents>(GameEvents::PolyframeToggle, "PolyframeToggle") {}
	virtual ~PolyframeToggleEvent();
};