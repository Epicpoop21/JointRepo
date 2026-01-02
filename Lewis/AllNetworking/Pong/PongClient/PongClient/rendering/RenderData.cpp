#include "RenderData.h"

unsigned int indices[6] = {
	0, 1, 2,
	1, 2, 3
};

RenderData::RenderData(glm::vec2 centre, int width, int height) : vb(nullptr, 0), ib(indices, sizeof(indices)), modelMatrix(glm::mat4(1.0f))
{
	values.push_back(glm::vec3(centre.x - (width * 0.5f), centre.y - (height * 0.5f), 0.0f));
	values.push_back(glm::vec3(centre.x + (width * 0.5f), centre.y - (height * 0.5f), 0.0f));
	values.push_back(glm::vec3(centre.x - (width * 0.5f), centre.y + (height * 0.5f), 0.0f));
	values.push_back(glm::vec3(centre.x + (width * 0.5f), centre.y + (height * 0.5f), 0.0f));

	for (glm::vec3 value : values) {
		std::cout << value.x << ", " << value.y << ", " << value.z << "\n";
	}

	vb.UpdateData(values.data(), values.size() * sizeof(glm::vec3));

	va.Bind();
	vb.Bind();
	ib.Bind();
	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	va.AddBuffer(vbl, vb);
}

RenderData::~RenderData()
{
}
