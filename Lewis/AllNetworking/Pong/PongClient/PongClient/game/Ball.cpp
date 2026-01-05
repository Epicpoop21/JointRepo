#include "Ball.h"

Ball::Ball(glm::vec2 centre) : Object(centre, 30, 30), horizontalSpeed(80.0f), verticalSpeed(20.0f)
{

}

Ball::~Ball()
{
}

void Ball::Move(glm::vec2 velocity)
{
	velocity.x -= 960.0f;
	velocity.y -= 540.0f;
	rd.modelMatrix = glm::mat4(1.0f);
	rd.modelMatrix = glm::translate(rd.modelMatrix, glm::vec3(velocity.x, velocity.y, 0.0f));
}
