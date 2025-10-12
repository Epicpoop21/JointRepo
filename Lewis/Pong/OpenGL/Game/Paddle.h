#pragma once
#include "../Renderer/Renderer.h"
#include <functional>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Paddle {
public:
	Paddle(RenderLayout* paddleLayout);
	~Paddle();

	void Move(int direction);
private:

public:
	glm::mat4 modelMatrix;
	RenderLayout* paddleLayout;
private:
};