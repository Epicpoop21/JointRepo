#include "UI.h"

UI::UI(Shader* shader) : vb(cursorDetail, sizeof(cursorDetail)), ib(indices, sizeof(indices)), shader(shader)
{
	std::cout << "Size of cursor VBO is: " << sizeof(cursorDetail) << "\n";
	std::cout << "Size of cursor IBO is: " << sizeof(indices) << "\n";
	VertexBufferLayout vbl;
	vbl.Push<float>(3);
	va.AddBuffer(vb, vbl);
}

UI::~UI()
{
}

void UI::Update()
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "2. ERROR IS: " << err << "\n";
	}
	shader->Use();
	shader->SetMat4f("projection", uiMatrix);
	va.Bind();
	ib.Bind();
	glDisable(GL_DEPTH_TEST);
	//glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, NULL);
	glEnable(GL_DEPTH_TEST);
	while ((err = glGetError()) != GL_NO_ERROR) {
		std::cout << "3. ERROR IS: " << err << "\n";
	}
}
