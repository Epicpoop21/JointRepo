#include "Ball.h"

Ball::Ball(glm::vec2 centre) : Object(centre, 30, 30), horizontalSpeed(80.0f), verticalSpeed(20.0f)
{

}

Ball::~Ball()
{
}