#pragma once

#include <unordered_map>
#include <iostream>

#include <glm/glm.hpp>

class Object
{
public:
	Object(glm::vec2 centre, int width, int height);
	~Object();

	virtual bool Move(glm::vec2 velocity);
	static Object* GetObjectByID(int id);
private:

public:
	int objectNum;
	glm::vec2 centre;
protected:
private:
	static inline std::unordered_map<int, Object*> objectMap;
	static inline int totalObjectNumber = 0;
};