#include <iostream>

#include "Game.h";

int main() {
	std::cout << "Hello world";

	Game game;
	
	std::cout << "GAME ENDED \n";
	if (game.StartUpdateLoop() == 1) {
		return 1;
	}
	

	return 1;
}