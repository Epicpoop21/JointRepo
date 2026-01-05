#pragma once
#include "../rendering/Renderer.h"
#include "../game/Object.h"

class Ball : public Object
{
public:
	Ball(glm::vec2 centre);
	~Ball();

	void Move(glm::vec2 velocity);
private:

public:
	
private:
	float verticalSpeed, horizontalSpeed;
};

