#pragma once

#include <vector>
#include <functional>

enum EventType {
	PAUSE,
	POLYFRAME,
	CLICK,
	COLLISION
};

template <typename T>
class Event
{
public:
	Event(EventType eventType) : m_EventType(eventType) {};
	~Event();
private:
	EventType m_EventType;
	std::vector<T> m_Listeners;
protected:
	bool m_Handled = false;
public:
	void AddListener(T func) { m_Listeners.push_back(func); };
	void InvokeEvent() {
		for (T func : m_Listeners) {
			func();
		}
	}
	bool GetHandled() const { return m_Handled; };
private:
	
};

class PauseEvent : public Event<std::function<void()>> 
{
public:
	PauseEvent() : Event(PAUSE) {}
};

class ClickEvent : public Event<std::function<void(int, int)>>
{
public:
	ClickEvent() : Event(CLICK) {}
};