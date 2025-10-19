#pragma once

#include <string>

template<typename T>
class Event {
protected:
	T m_Type; //Type of event- "GameEvent" etc
	std::string m_Name; 
	bool m_Handled = false;
public:
	Event() = default;
	Event(T type, const std::string& name = "") : m_Type(type), m_Name(name) {}
	virtual ~Event() {};
	inline const T GetType() const { return m_Type; }; //Getter for event type

	template <typename EventType>
	inline EventType ToType() const {
		return static_cast<const EventType>(*this);
	}
	inline const std::string& GetName() const { return m_Name; };
	virtual bool Handled() const { return m_Handled; };
};