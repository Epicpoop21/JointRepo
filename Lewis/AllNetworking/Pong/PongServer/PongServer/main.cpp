#include <iostream>
#include <string>
#include "UDPHandler.h"

#include "GLFW/glfw3.h"

int main() {
	glfwInit();
	UDPHandler handler("0.0.0.0", 55555);

	while (true) {
		handler.GetDataInSocket();
	}

	return 1;
}