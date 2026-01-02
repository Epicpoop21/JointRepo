#pragma once
#include "../rendering/Renderer.h"
#include "../game/Object.h"

class Ball : public Object
{
public:
	Ball(glm::vec2 centre);
	~Ball();

	void Move(int horizontalDirection, int verticalDirection, float speed);
private:

public:
	
private:
	float verticalSpeed, horizontalSpeed;
};

