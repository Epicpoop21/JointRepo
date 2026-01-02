#include "Object.h"
#include "Game.h"

Object::Object(glm::vec2 centre, int width, int height) : objectNum(totalObjectNumber), rd(centre, width, height)
{
	objectMap[objectNum] = this;
	totalObjectNumber++;
}

Object::~Object()
{
}

void Object::Move(glm::vec2 velocity)
{
	rd.modelMatrix = glm::translate(rd.modelMatrix, glm::vec3(velocity.x, velocity.y, 0.0f));
}

Object* Object::GetObjectByID(int id)
{
	auto it = objectMap.find(id);
	if (it != objectMap.end()) return it->second;
	return nullptr;
}
