#pragma once

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
	STONE
};

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