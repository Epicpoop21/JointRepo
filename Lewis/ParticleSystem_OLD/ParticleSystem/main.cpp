#include <iostream>
#include "Program/Game.h"

int main() {
	std::cout << "Started up \n";

	Game game;
	
	game.StartUpdateLoop();
	
	std::cout << "Terminated \n";
	return 1;
}