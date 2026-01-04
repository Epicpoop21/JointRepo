#include "Object.h"

Object::Object(glm::vec2 centre, int width, int height) : objectNum(totalObjectNumber), centre(centre)
{
	objectMap[objectNum] = this;
	totalObjectNumber++;
}

Object::~Object()
{
}

bool Object::Move(glm::vec2 velocity)
{
	return false;
}

Object* Object::GetObjectByID(int id)
{
	auto it = objectMap.find(id);
	if (it != objectMap.end()) return it->second;
	return nullptr;
}
