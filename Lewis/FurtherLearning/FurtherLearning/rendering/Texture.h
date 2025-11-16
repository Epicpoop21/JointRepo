#pragma once

#include <glad/glad.h>
#include <stb_image/stb_image.h>

class Texture
{
public:
	Texture(const char* filePath);
	~Texture();
	void Bind();
	void Unbind();
private:

public:
	unsigned int m_TextureID;
	int width, height;
	int numOfChannels;
	unsigned char* data;
	const char* filepath;
private:
};

