#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct xyCoord {
	float x;
	float y;
};

struct RenderLayout {
	VertexArray va;
	VertexBuffer vb;
	VertexBufferLayout vbl;
	IndexBuffer ib;

	bool isCircle = false;   // distinguish rectangle/circle
	float radius = 0.0f;     // used only for circles
	xyCoord centre{ 0.0f, 0.0f };  

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	RenderLayout(VertexArray&& va, VertexBuffer&& vb, VertexBufferLayout&& vbl, IndexBuffer&& ib,
		bool isCircle, float radius, xyCoord centre, glm::mat4 modelMatrix)
		: va(std::move(va)), vb(std::move(vb)), vbl(std::move(vbl)), ib(std::move(ib)),
		isCircle(isCircle), radius(radius), centre(centre), modelMatrix(modelMatrix) {}
};

class Renderer {
public:

private:
	Shader shader;

public:
	Renderer() = default;
	Renderer(Shader& shader);
	~Renderer();
	RenderLayout CreateRectangle(xyCoord coords, float width, float height);
	RenderLayout CreateCircle(float centreX, float centreY, float radius);
	RenderLayout CreateTriangle(const void* data);

	void RenderRectangle(RenderLayout& object);
	void RenderCircle(RenderLayout& object);
};