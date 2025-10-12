#include "Bird.h"

Bird::Bird(RenderLayout&& layout) 
	:layout(std::move(layout))
{
	x = 0;
	currentY = 540.0f;
}

Bird::~Bird()
{

}

void Bird::Fall()
{

	x = x + 0.2f;
	layout.centre.y = currentY + (-0.075 * (x * x)) + (6 * x);
	if (layout.centre.y < 0) {
		currentY = 540.0f;
		x = 0;
	}
	//std::cout << "X is: " << x << " Y is: " << (-0.3 * (x * x)) + (3 * x) << "\n";
}

void Bird::Jump()
{
	currentY = layout.centre.y;
	x = 0;
}

