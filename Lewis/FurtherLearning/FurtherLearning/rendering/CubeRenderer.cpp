#include "CubeRenderer.h"

CubeRenderer::CubeRenderer() : cubeData{}, ivb(nullptr, 0), pcvb(nullptr, 0), ib(indices, sizeof(indices))
{
	for (int x = 0; x < 100; x++) {
		for (int z = 0; z < 100; z++) {
			cubeData.push_back(glm::vec4(x, 0.0f, z, 0.0f));
		}
	}

	VertexBufferLayout pcvbl;
	VertexBufferLayout ivbl;
	pcvb.UpdateData(instancePos, sizeof(instancePos));
	ivb.UpdateData(cubeData.data(), cubeData.size() * sizeof(glm::vec3));
	ib.UpdateData(indices, sizeof(indices));
	pcvbl.Push<float>(3);
	pcvbl.Push<float>(3);
	ivbl.Push<float>(3);

	va.AddBuffer(pcvb, pcvbl);
	va.AddBuffer(ivb, ivbl);
	va.Bind();
	glVertexAttribDivisor(2, 1);
}

CubeRenderer::~CubeRenderer()
{

}

void CubeRenderer::Render()
{
	va.Bind();
	ib.Bind();
	glDrawElementsInstanced(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr, cubeData.size());
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cerr << "OpenGL Error - Code: " << err << std::endl;
	}
}


