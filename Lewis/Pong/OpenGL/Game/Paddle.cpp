#include "Paddle.h"

Paddle::Paddle(RenderLayout* paddleLayout)
	:paddleLayout(paddleLayout)
{
	modelMatrix = glm::mat4(1.0f);
}

Paddle::~Paddle()
{
}

void Paddle::Move(int direction)
{
	if (direction == 1 && paddleLayout->centre.y + 100.0f < 1080.0f) {
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 10.0f, 0.0f));
		paddleLayout->centre.y += 10.0f;
	}
	else if (paddleLayout->centre.y - 100.0f > 0.0f) {
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -10.0f, 0.0f));
		paddleLayout->centre.y -= 10.0f;
	}
}
