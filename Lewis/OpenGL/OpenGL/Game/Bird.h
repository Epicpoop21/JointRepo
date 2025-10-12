#pragma once
#include "../Renderer/Renderer.h"

class Bird {
public:
	Bird() = default;
	Bird(RenderLayout&& layout);
	~Bird();
	
	void Fall();
	void Jump();
private:

public:
	RenderLayout layout;
private:
	float x;
	float currentY;
	bool pause;
};