#include "Renderer.h"
#include <vector>

Renderer::Renderer(Shader& shader)
	:shader(shader)
{

}

Renderer::~Renderer()
{

}

RenderLayout Renderer::CreateRectangle(xyCoord coords, float width, float height)
{
	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};
	IndexBuffer ib(indices, sizeof(indices));

	std::vector<float> data;
	data.push_back(-width / 2.0f); data.push_back(-height / 2.0f); data.push_back(0.0f);
	data.push_back(-width / 2.0f); data.push_back(height / 2.0f); data.push_back(0.0f);
	data.push_back(width / 2.0f); data.push_back(-height / 2.0f); data.push_back(0.0f);
	data.push_back(width / 2.0f); data.push_back(height / 2.0f); data.push_back(0.0f);

	VertexBuffer vb(data.data(), data.size() * sizeof(float));

	VertexArray va;
	VertexBufferLayout vbl;

	vbl.Push<float>(3);
	va.AddBuffer(vb, vbl);

	glm::mat4 mat(1.0f);

	RenderLayout object = {std::move(va), std::move(vb), std::move(vbl), std::move(ib), false, 0.0f, coords, mat };
	return object;
}


RenderLayout Renderer::CreateCircle(float centreX, float centreY, float radius)
{
	unsigned int indices[] = {
		0, 1, 2,
		1, 2, 3
	};

	IndexBuffer ib(indices, sizeof(indices));

	std::vector<float> data;
	data.push_back(0.0f);
	data.push_back(0.0f);
	data.push_back(0.0f);
	
	data.push_back(0.0f);
	data.push_back(1080.0f);
	data.push_back(0.0f);

	data.push_back(1920.0f);
	data.push_back(0.0f);
	data.push_back(0.0f);

	data.push_back(1920.0f);
	data.push_back(1080.0f);
	data.push_back(0.0f);

	VertexBuffer vb(data.data(), data.size() * sizeof(float));

	VertexArray va;
	VertexBufferLayout vbl;

	vbl.Push<float>(3);
	va.AddBuffer(vb, vbl);

	glm::mat4 mat(1.0f);

	RenderLayout object = { std::move(va), std::move(vb), std::move(vbl), std::move(ib), true, radius, {centreX, centreY}, mat };

	return object;
}
/*
RenderLayout Renderer::CreateTriangle(const void* data)
{
	RenderLayout layout;
	return layout;
}
*/

void Renderer::RenderRectangle(RenderLayout& object)
{
	shader.Use();
	shader.SetFloatVec4("colorValue", 0.5f, 0.2f, 0.7f, 1.0f);
	shader.SetBool("circle", false);
	shader.SetFloatMat4("model", 1, GL_FALSE, glm::value_ptr(object.modelMatrix));
	object.va.Bind();
	object.ib.Bind();
	object.vb.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderer::RenderCircle(RenderLayout& object)
{
	shader.Use();
	shader.SetFloatVec4("colorValue", 0.5f, 0.2f, 0.7f, 1.0f);
	shader.SetBool("circle", true);
	shader.SetFloatMat4("model", 1, GL_FALSE, glm::value_ptr(object.modelMatrix));
	shader.SetFloatVec2("centre", object.centre.x, object.centre.y);
	shader.SetFloat("radius", object.radius);
	object.va.Bind();
	object.ib.Bind();
	object.vb.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
