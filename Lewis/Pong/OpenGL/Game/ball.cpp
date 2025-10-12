#include "ball.h"

Ball::Ball(RenderLayout& ballLayout)
	:ballLayout(ballLayout)
{
	velocity = 10.0f;
	direction = { 1, 0.5 };

	eventHandler->GameEventDispatcher.AddListener(GameEvents::PauseToggle,
		std::bind(&Ball::Pause, this, std::placeholders::_1));
}

Ball::~Ball()
{

}

void Ball::Move()
{
	if (ballLayout.centre.x > 1920.0f - ballLayout.radius || ballLayout.centre.x < 0.0f + ballLayout.radius) {
		ballLayout.centre = { 960.0f, 540.0f };
		eventHandler->FireGameEvent(GameEvents::Restart);
		eventHandler->FireGameEvent(GameEvents::PauseToggle);
	}

	if (ballLayout.centre.y > 1080.0f - ballLayout.radius || ballLayout.centre.y < 0.0f + ballLayout.radius) {
		direction.y = direction.y * -1;
	}
	ballLayout.centre.x += velocity * direction.x;
	ballLayout.centre.y += velocity * direction.y;
}

void Ball::ReflectPaddle()
{
	direction.x = direction.x * -1;
}

void Ball::Pause(const Event<GameEvents>& event) {
	paused = !paused;
	if (paused) {
		velocity = 0.0f;
	}
	else {
		velocity = 10.0f;
	}
}
