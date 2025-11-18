#pragma once
#include "Block.h"
#include <map>

#include "../rendering/Texture.h"

class CubeTextures
{
public:
	CubeTextures();
	~CubeTextures();

	Texture GetTexture(BlockType type);
private:

public:
	std::map<BlockType, Texture> textureMap;
private:

};

