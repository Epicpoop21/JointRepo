#include "Block.h"

BlockTextureInfo BLOCK_DATABASE[4] = {
	//AIR
	{{0, 0}, {0, 0}, {0, 0}},
	//GRASS
	{{1, 0}, {2, 0}, {3, 0}},
	//DIRT
	{{3 ,0}, {3, 0}, {3, 0}}
};

Block::Block(glm::vec3 position, BlockType type) : position(position), type(type)
{

}

Block::~Block()
{
}
