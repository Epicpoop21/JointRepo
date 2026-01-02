#include "Paddle.h"

Paddle::Paddle(int side, glm::vec2 centre) : side(side), Object(centre, 20, 160)
{

}

Paddle::~Paddle()
{
}
