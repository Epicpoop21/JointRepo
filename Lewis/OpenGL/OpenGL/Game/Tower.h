#pragma once
#include "../Renderer/Renderer.h"

class Tower {
public: 
	Tower() = default;
	Tower(RenderLayout&& upperTower, RenderLayout&& lowerTower);
	~Tower();
private:

public:
	RenderLayout upperTower;
	RenderLayout lowerTower;

	int yOffset;

	float bottomTowerTopCoord;
	float topTowerBottomCoord;
};