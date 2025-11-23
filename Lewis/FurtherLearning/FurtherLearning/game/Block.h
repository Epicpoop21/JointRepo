#pragma once
#pragma message("Compiling Block.h")
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat2x2.hpp>
#include <glm/gtc/type_ptr.hpp>

enum CubeFace {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	FRONT,
	BACK
};

enum BlockType {
	AIR,
	GRASS,
	DIRT,
	STONE,
	BEDROCK,
	OAKLOG,
	LEAF
};

struct BlockTextureInfo {
	glm::ivec2 uvTop;
	glm::ivec2 uvSide;
	glm::ivec2 uvBottom;
};

extern BlockTextureInfo BLOCK_DATABASE[7];

class Block {
public:
	Block() = default;
	Block(glm::vec3 position, BlockType type);
	~Block();
private:

public:
	glm::vec3 position;
	BlockType type;
private:

};