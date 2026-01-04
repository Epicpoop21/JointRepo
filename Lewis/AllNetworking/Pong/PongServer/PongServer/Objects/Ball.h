#pragma once
#include "./Object.h"

class Ball : public Object
{
public:
	Ball(glm::vec2 centre);
	~Ball();

	bool Move(glm::vec2 velocity);
private:

public:
	glm::vec2 currentVelocity;
private:
	bool moving;
};

