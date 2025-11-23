#pragma once
#include <memory>
#include "../rendering/Shader.h"
#include "../rendering/VertexArray.h"
#include "../rendering/IndexBuffer.h"

class UI
{
public:
	UI(Shader* shader);
	~UI();

	void Update();
private:

public:

private:
	Shader* shader;

	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;

	glm::mat4 uiMatrix = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f);

	float cursorDetail[24] = {
		940.0f,  500.0f, 0.0f,
		980.0f,  500.0f, 0.0f,
		940.0f,  580.0f, 0.0f,
		980.0f,  580.0f, 0.0f,
					 	 
		920.0f,  520.0f, 0.0f,
		1000.0f, 520.0f, 0.0f,
		920.0f,  560.0f, 0.0f,
		1000.0f, 560.0f, 0.0f
	};

	unsigned int indices[12] = {
		0, 1, 2,
		1, 2, 3,

		4, 5, 6,
		5, 6, 7
	};
};

