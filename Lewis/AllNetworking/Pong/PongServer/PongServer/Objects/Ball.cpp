#include "Ball.h"

Ball::Ball(glm::vec2 centre) : Object(centre, 30, 30), moving(true), currentVelocity(glm::vec2(10.0f, 2.0f))
{

}

Ball::~Ball()
{
}

bool Ball::Move(glm::vec2 velocity) {
	if (centre.y + 30.0f + velocity.y > 1080.0f || centre.y - 30.0f + velocity.y < 0.0f) { currentVelocity.y *= -1; return false; }
	if (centre.x + 30.0f + velocity.x > 1920.0f || centre.x - 30.0f + velocity.x < 0.0f) { currentVelocity.x *= -1; return false; }
	centre += velocity;
	return true;
}