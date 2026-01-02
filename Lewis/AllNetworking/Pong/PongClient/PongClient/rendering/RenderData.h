#pragma once
#include <vector>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

extern unsigned int indices[6];

class RenderData
{
public:
	RenderData(glm::vec2 centre, int width, int height);
	~RenderData();
private:

public:
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
	glm::mat4 modelMatrix;
private:
	std::vector<glm::vec3> values;
};

