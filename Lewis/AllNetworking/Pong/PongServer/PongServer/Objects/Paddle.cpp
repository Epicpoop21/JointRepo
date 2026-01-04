#include "Paddle.h"

Paddle::Paddle(glm::vec2 centre) : Object(centre, 20, 160)
{

}

Paddle::~Paddle()
{
}

bool Paddle::Move(glm::vec2 velocity) {
	if (centre.y + 80 + velocity.y > 1080 || centre.y - 80 + velocity.y < 0) return false;
	centre += velocity;
	return true;
}