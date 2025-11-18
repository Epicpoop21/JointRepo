#include "CubeTextures.h"

CubeTextures::CubeTextures()
{
	textureMap.emplace(GRASS ,Texture("res/textures/Grass.png"));
	textureMap.emplace(DIRT, Texture("res/textures/Dirt.png"));
	textureMap.emplace(STONE, Texture("res/textures/Stone.png"));
}

CubeTextures::~CubeTextures()
{
}

Texture CubeTextures::GetTexture(BlockType type)
{
	return textureMap.at(type);
}
