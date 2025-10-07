#include "StatRecorder.h"
#include "../Stats/Gliders.h"

StatRecorder::StatRecorder()
{
	LoadFromFile("data.json");
}

void StatRecorder::AddGlider()
{
	std::string BGAReg, gliderType;
	time_t annualValidUntil, arcValidUntil, insuredUntil, nextWeighing;
	int minutesInAir, winchLaunches, aerotowLaunches;
	
	std::cout << "Enter BGA registration: "; std::cin >> BGAReg;
	std::cin.ignore();
	std::cout << "Enter glider type: "; std::getline(std::cin, gliderType);
	std::cout << "ALL TIMES GIVEN MUST BE UNIX TIMESTAMPS\n";
	std::cout << "Enter annual expiary date: "; std::cin >> annualValidUntil;
	std::cout << "Enter ARC expiary date: "; std::cin >> arcValidUntil; 
	std::cout << "Enter insurance expiary date: "; std::cin >> insuredUntil;
	std::cout << "Enter date of next weighing: "; std::cin >> nextWeighing;
	std::cout << "Enter total minutes on the airframe: "; std::cin >> minutesInAir;
	std::cout << "Enter number of winch launches: "; std::cin >> winchLaunches;
	std::cout << "Enter number of aerotows: "; std::cin >> aerotowLaunches;

	Glider glider(GliderInfo{ BGAReg, gliderType, annualValidUntil, arcValidUntil, insuredUntil, nextWeighing, minutesInAir, winchLaunches, aerotowLaunches });
	gliders.push_back(glider);
	SaveToFile("data.json");
}

GliderInfo* StatRecorder::ReturnGliderInfo(std::string& gliderBGAReg)
{
	for (Glider& glider : gliders) {
		if (glider.info.gliderBGAReg == gliderBGAReg) {
			return &glider.info;
		}
	}
	std::cout << "Glider with that reg cannot be found. \n";
	return nullptr;
}

void StatRecorder::PrintGliderInfo(GliderInfo& gliderInfo)
{
	std::cout << "Info for glider " << gliderInfo.gliderBGAReg << "(" << gliderInfo.gliderType << ")\n";

	std::cout << "\n==================IMPORTANT DATES==================\n";
	std::cout << "Annual valid until: "; PrintTime(gliderInfo.annualValidUntil); std::cout << "\n";
	std::cout << "ARC valid until: "; PrintTime(gliderInfo.arcValidUntil); std::cout << "\n";
	std::cout << "Insurance is valid until: "; PrintTime(gliderInfo.insuredUntil); std::cout << "\n";
	std::cout << "Weighing required on: "; PrintTime(gliderInfo.nextWeighing); std::cout << "\n";
			 
	std::cout << "\n==================IMPORTANT FIGURES==================\n";
	std::cout << "Number of winch launches: " << gliderInfo.winchLaunches << "\n";
	std::cout << "Number of aerotow launches: " << gliderInfo.aerotowLaunches << "\n";
	std::cout << "Total launches: " << gliderInfo.aerotowLaunches + gliderInfo.winchLaunches << "\n";
	std::cout << "Airframe minutes: " << gliderInfo.minutesInAir << "\n";
	ConvertMinutes(gliderInfo.minutesInAir);
	std::cout << "Airframe hours: " << minutesAndHours[0] << " (+" << minutesAndHours[1] << "mins)" << "\n";

	std::cout << "\n \n";
}

void StatRecorder::ChangeValue(GliderInfo& infoToModify)
{
	std::string fieldToChange;
	std::string newValue;
	std::cout << "\nSelect field to change. For dates, they MUST be a unix timestamp.\n";
	std::cout << "1. Annual date \n";
	std::cout << "2. ARC date \n";
	std::cout << "3. Insurance date \n";
	std::cout << "4. Weighing date \n";

	std::cout << "Enter value to change: ";
	std::cin >> fieldToChange;

	std::cout << "Enter new value for field: ";
	std::cin >> newValue;

	if (fieldToChange == "1") {
		infoToModify.annualValidUntil = std::stoi(newValue);
	}
	else if (fieldToChange == "2") {
		infoToModify.arcValidUntil = std::stoi(newValue);
	}
	else if (fieldToChange == "3") {
		infoToModify.insuredUntil = std::stoi(newValue);
	}
	else if (fieldToChange == "4") {
		infoToModify.nextWeighing = std::stoi(newValue);
	}
}

int StatRecorder::LoadFromFile(const std::string& filePath)
{
	std::ifstream jsonFileStream("./data.json");
	if (!jsonFileStream.is_open()) {
		std::cout << "FILE TO SAVE TO DOES NOT EXIST \n";
		gliders.clear();
		return -1;
	}

	if (jsonFileStream.peek() == std::ifstream::traits_type::eof()) {
		std::cerr << "JSON file is empty. \n";
		return 0;
	}

	json j;
	jsonFileStream >> j;

	if (j.contains("gliders")) {
		std::vector<GliderInfo> infos = j["gliders"].get<std::vector<GliderInfo>>();
		for (auto& info : infos) {
			Glider glider(info);
			gliders.push_back(glider);
		}
	}
	else {
		std::cout << "No gliders found in JSON file.\n";
	}
}

void StatRecorder::SaveToFile(const std::string& filePath)
{
	json j;
	j["gliders"] = gliders;

	std::ofstream out(filePath);
	if (!out.is_open()) {
		throw std::runtime_error("Couldn't open file at " + filePath + " for writing");
	}
	out << j.dump(4);
}

void StatRecorder::PrintTime(time_t time)
{
	struct tm datetime;
	localtime_s(&datetime, &time);
	strftime(timeText, 100, "%d/%m/%Y", &datetime);
	std::cout << timeText;
}

void StatRecorder::ConvertMinutes(int minutes)
{
	minutesAndHours[0] = minutes / 60;
	minutesAndHours[1] = minutes % 60;
}

