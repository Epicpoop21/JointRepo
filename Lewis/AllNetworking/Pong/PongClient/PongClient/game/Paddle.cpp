#include "Paddle.h"

Paddle::Paddle(int side, glm::vec2 centre) : side(side), Object(centre, 20, 160)
{

}

Paddle::~Paddle()
{
}

void Paddle::Move(glm::vec2 velocity) {
	rd.modelMatrix = glm::translate(rd.modelMatrix, glm::vec3(velocity.x, velocity.y, 0.0f));
}