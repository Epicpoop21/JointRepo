#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "shader.h"

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
	xyCoord centre{ 0.0f, 0.0f };  // optional: store circle center
};

class Renderer {
public:

private:
	Shader shader;

public:
	Renderer() = default;
	Renderer(Shader& shader);
	~Renderer();
	RenderLayout CreateRectangle(float centreX, float centreY, float width, float height);
	RenderLayout CreateCircle(float centreX, float centreY, float radius);
	RenderLayout CreateTriangle(const void* data);

	void RenderRectangle(RenderLayout& object);
	void RenderCircle(RenderLayout& object);
};