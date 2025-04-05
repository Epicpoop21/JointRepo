#include <iostream>
#include <string>

void reverseString();

int main() {
	reverseString();
}

void reverseString() {
	std::string inputString;

	std::cout << "Input string to reverse: ";
	std::getline(std::cin, inputString);

	int stringLength = inputString.length();
	std::string newString = "";

	for (; stringLength >= 0; stringLength--) {
		newString = newString + inputString[stringLength];
	}
	std::cout << newString;
}