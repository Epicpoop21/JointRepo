#pragma once
#include "./Object.h"

class Ball : public Object
{
public:
	Ball(glm::vec2 centre);
	~Ball();

	bool Move(glm::vec2 velocity);
	void CheckCollisions(glm::vec2& leftPaddleCentre, glm::vec2& rightPaddleCentre);
private:

public:
	glm::vec2 currentVelocity;
private:
	bool moving;
	int ballRadius = 15.0f;
};

