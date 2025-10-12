#pragma once

#include <map>
#include <functional>
#include <vector>

template <typename T>
class EventDispatcher {
private:
	//Creating a type Func that stores a function returning void and takes an event
	unsigned int m_NextListenerID = 1;
	using Func = std::function<void(const Event<T>&)>;

	struct EventListener {
		unsigned int listenerID;
		Func func;
	};

	std::map < T, std::vector<EventListener>> m_Listeners;

public:
	unsigned int AddListener(T type, const Func& func) {
		unsigned int id = m_NextListenerID++;
		m_Listeners[type].push_back({id, func});
		return id;
	}
	void RemoveListener(T type, unsigned int listenerID) {
		auto& listeners = m_Listeners[type];
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
			[listenerID](const EventListener& listener) {
				return listener.listenerID == listenerID;
			}), listeners.end());
	}

	
	//Sends events to all listeners
	void SendEvent(const Event<T>& event) {
		if (m_Listeners.find(event.GetType()) == m_Listeners.end()) {
			return;
		}

		for (auto&& listener : m_Listeners.at(event.GetType())) {
			if (!event.Handled()) {
				listener.func(event);
			}
		}
	}
};