#pragma once
#include "./Object.h"

class Paddle : public Object
{
public:
	Paddle(glm::vec2 centre);
	~Paddle();

	bool Move(glm::vec2 velocity);
private:

public:

private:

};

