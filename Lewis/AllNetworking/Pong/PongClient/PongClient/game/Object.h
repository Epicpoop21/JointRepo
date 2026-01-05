#pragma once

#include <unordered_map>

#include "../rendering/Renderer.h"

class Game;

class Object
{
public:
	Object(glm::vec2 centre, int width, int height);
	~Object();

	virtual void Move(glm::vec2 velocity);
	static Object* GetObjectByID(int id);
private:

public:
	RenderData rd;
	int objectNum;
private:
	static inline std::unordered_map<int, Object*> objectMap;
	static inline int totalObjectNumber = 0;
};

