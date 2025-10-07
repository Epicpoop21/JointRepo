#include <iostream>
#include "Stats/Gliders.h"
#include "Recording/StatRecorder.h"

int main()
{
	StatRecorder recorder;
	std::cout << "Initialising database\n";

	Glider R19Glider(GliderInfo{ time(NULL), time(NULL), time(NULL), time(NULL), "K21", "R19", 372813, 1, 1, 2});
	recorder.AddGlider(R19Glider);

	std::string selectedOption;
	bool running = true;
	while (running) {
		
		std::cout << "1. Load data from new GlideX sheet. \n";
		std::cout << "2. Check records for specific glider. \n";
		std::cout << "3. Update records for specific glider. \n";
		std::cout << "4. More specific functions. \n";

		std::cout << "Input option: ";
		std::cin >> selectedOption;

		if (selectedOption == "1") {
			std::cout << "Loading data \n";
		}
		else if (selectedOption == "2") {
			std::string gliderToRetrieve;
			std::cout << "Enter glider's BGA registration: ";
			std::cin >> gliderToRetrieve;
			GliderInfo& gliderInfo = recorder.ReturnGliderInfo(gliderToRetrieve);
			recorder.PrintGliderInfo(gliderInfo);
		}
		else if (selectedOption == "3") {
			std::string gliderToRetrieve;
			std::cout << "Enter glider's BGA registration: ";
			std::cin >> gliderToRetrieve;
			GliderInfo& gliderInfo = recorder.ReturnGliderInfo(gliderToRetrieve);
			recorder.ChangeValue(gliderInfo);
		}

		std::cin.get();
	}
}