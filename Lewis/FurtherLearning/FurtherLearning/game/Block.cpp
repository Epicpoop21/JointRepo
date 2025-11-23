#include "Block.h"

BlockTextureInfo BLOCK_DATABASE[7] = {
	//TOP    BOTTOM    SIDE
	//AIR
	{{0, 0}, {0, 0}, {0, 0}},
	//GRASS
	{{1, 0}, {3, 0}, {2, 0}},
	//DIRT
	{{3 ,0}, {3, 0}, {3, 0}}, 
	//STONE
	{{4 ,0}, {4, 0}, {4, 0}},
	//BEDROCK
	{{5, 0}, {5, 0}, {5, 0}},
	//OAK LOG
	{{6, 0}, {6, 0}, {7, 0}},
	//LEAF
	{{8, 0}, {8, 0}, {8, 0}}
};

Block::Block(glm::vec3 position, BlockType type) : position(position), type(type)
{

}

Block::~Block()
{
}
