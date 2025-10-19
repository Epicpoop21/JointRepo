#pragma once

#include <map>
#include <functional>
#include <vector>

template <typename T>
class EventDispatcher {
private: 
	unsigned int m_NextListenerID = 1;
	//Create type Func that stores a function taking in an event and returning void
	using Func = std::function<void(const Event<T>&)>;

	struct EventListener {
		unsigned int listenerID;
		Func func;
	};

	std::map <T, std::vector<EventListener>> m_Listeners;

public:
	unsigned int AddListener(T type, const Func& func) {
		unsigned int id = m_NextListenerID++;
		m_Listeners[type].push_back({ id, func });
		return id;
	}
	void RemoveListener(T type, unsigned int listenerID) {
		auto& listeners = m_Listeners[type];
		listeners.erase(std::remove_if(listeners.begin(), listeners.end(),
			[listenerID](const EventListener& listener) {
				return listener.listenerID == listenerID;
			}), listeners.end());
	}

	//For each listener in the list of listeners for that event type, fire the event
	void SendEvent(const Event<T>& event) {
		//Return if got to the end of the list
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