#include "Paddle.h"

Paddle::Paddle(glm::vec2 centre) : Object(centre, 20, 160)
{

}

Paddle::~Paddle()
{
}

bool Paddle::Move(glm::vec2 velocity) {
	if (centre.y + 80.0f + velocity.y > 1080.0f || centre.y - 80.0f + velocity.y < 0.0f) return false;
	centre += velocity;
	return true;
}