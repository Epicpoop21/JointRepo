#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include <vector>

class CubeRenderer {
public:
	CubeRenderer();
	~CubeRenderer();
	void Render();
private:

public:

private:
	VertexArray va;
	VertexBuffer ivb;
	VertexBuffer pcvb;
	IndexBuffer ib;

	std::vector<glm::vec4> cubeData;

	float instancePos[48] = {
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 1.0f, //0
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f, //1
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f, //2
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f, //3

		 //LEFT FACE
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, //4
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f, //5

		//RIGHT FACE
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f, //6
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f  //7
	};

	unsigned int indices[36] = {
		//FRONT FACE
		0, 2, 1,
		1, 2, 3,

		//LEFT FACE
		0, 1, 4,
		0, 4, 5,

		//RIGHT FACE
		2, 6, 3,
		2, 7, 6,

		//TOP FACE
		1, 3, 4,
		3, 6, 4,

		//BOTTOM FACE
		0, 5, 2,
		2, 5, 7,

		//BACK FACE
		5, 4, 6,
		5, 6, 7
	};
};