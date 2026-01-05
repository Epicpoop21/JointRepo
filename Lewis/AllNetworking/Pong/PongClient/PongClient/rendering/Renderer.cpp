#include "Renderer.h"

Renderer::Renderer()
{
	projection = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, 0.0f, 100.0f);
	shader = Shader("./vertex.s", "./frag.s");
	view = glm::mat4(1.0f);
}

Renderer::~Renderer()
{

}

void Renderer::Render(RenderData& rd, int pointsToRender)
{
	shader.Use();
	shader.SetMat4f("model", rd.modelMatrix);
	shader.SetMat4f("view", view);
	shader.SetMat4f("projection", projection);

	rd.va.Bind();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL); 
	rd.va.Unbind();
}
