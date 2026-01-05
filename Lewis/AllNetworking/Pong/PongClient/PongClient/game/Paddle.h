#pragma once
#include "../rendering/Renderer.h"
#include "../game/Object.h"

class Paddle : public Object
{
public:
	Paddle(int side, glm::vec2 centre);
	~Paddle();

	void Move(glm::vec2 velocity);
private:

public:

private:
	int side;
};

