#include "Ball.h"

Ball::Ball(glm::vec2 centre) : Object(centre, 30, 30), moving(true), currentVelocity(glm::vec2(10.0f, 2.0f))
{

}

Ball::~Ball()
{
}

bool Ball::Move(glm::vec2 velocity) {
	if (centre.y + 30.0f > 1080.0f || centre.y - 30.0f < 0.0f) {
		currentVelocity.y *= -1; 
		centre += currentVelocity;
		return true;
	}

	if (centre.x + 30.0f > 1920.0f || centre.x - 30.0f < 0.0f) {
		currentVelocity.x *= -1; 
		centre += currentVelocity;
		return true; 
	}

	std::cout << "BALL CENTRE IS: " << centre.x << ", " << centre.y << "\n";
	centre += currentVelocity;
	return true;
}