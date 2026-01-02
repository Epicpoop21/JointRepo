#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RenderData.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render(RenderData& rd, int pointsToRender);
private:

public:
	Shader shader;
private:
	glm::mat4 projection;
	glm::mat4 view;
};

