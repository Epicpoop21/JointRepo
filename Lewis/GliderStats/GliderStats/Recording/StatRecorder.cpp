#include "StatRecorder.h"

StatRecorder::StatRecorder()
{

}

void StatRecorder::AddGlider(Glider glider)
{
	gliders.push_back(glider);
}

GliderInfo& StatRecorder::ReturnGliderInfo(std::string& gliderBGAReg)
{
	for (Glider& glider : gliders) {
		if (glider.info.gliderBGAReg == gliderBGAReg) {
			return glider.info;
		}
	}
	std::cout << "Glider with that reg cannot be found. \n";
}

void StatRecorder::PrintGliderInfo(GliderInfo& gliderInfo)
{
	std::cout << "Info for glider " << gliderInfo.gliderBGAReg << "(" << gliderInfo.gliderType << ")\n";

	std::cout << "\n ==================IMPORTANT DATES==================\n";
	std::cout << "Last annual was on: "; PrintTime(gliderInfo.annualValidUntil); std::cout << "\n";
	std::cout << "Last ARC was on: "; PrintTime(gliderInfo.arcValidUntil); std::cout << "\n";
	std::cout << "Insurance is valid until: "; PrintTime(gliderInfo.insuredUntil); std::cout << "\n";
	std::cout << "Last weighing was on: "; PrintTime(gliderInfo.nextWeighing); std::cout << "\n";
			 
	std::cout << "\n ==================IMPORTANT FIGURES==================\n";
	std::cout << "Number of winch launches: " << gliderInfo.winchLaunches << "\n";
	std::cout << "Number of aerotow launches: " << gliderInfo.aerotowLaunches << "\n";
	std::cout << "Total launches: " << gliderInfo.totalLaunches << "\n";
	std::cout << "Airframe minutes: " << gliderInfo.minutesInAir << "\n";
	ConvertMinutes(gliderInfo.minutesInAir);
	std::cout << "Airframe hours: " << minutesAndHours[0] << " (+" << minutesAndHours[1] << "mins)" << "\n";

	std::cout << "\n \n";
}

void StatRecorder::ChangeValue(GliderInfo& infoToModify)
{
	std::string fieldToChange;
	std::string newValue;
	std::cout << "\n \n Select field to change. For dates, they MUST be a unix timestamp.\n";
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
		std::cout << "TEST: " << infoToModify.annualValidUntil << "\n";
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

	std::cout << "Value changed to " << newValue << "\n";
}

void StatRecorder::LoadFromFile(std::string& filePath)
{
	std::ifstream jsonFileStream("./data.json");
	nlohmann::json jsonData = nlohmann::json::parse(jsonFileStream);

}

void StatRecorder::SaveToFile(std::string& filePath)
{
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

void StatRecorder::to_json(nlohmann::json& j, const GliderInfo& g) {
	j = nlohmann::json{
		{"gliderType", g.gliderType},
		{"gliderBGAReg", g.gliderBGAReg},
		{"annualValidUntil", g.annualValidUntil},
		{"arcValidUntil", g.arcValidUntil},
		{"insuredUntil", g.insuredUntil},
		{"nextWeighing", g.nextWeighing},
		{"minutesInAir", g.minutesInAir},
		{"winchLaunches", g.winchLaunches},
		{"aerotowLaunches", g.aerotowLaunches}
	};
}

void from_json(const nlohmann::json& j, GliderInfo& g) {
	j.at("gliderType").get_to(g.gliderType);
	j.at("gliderBGAReg").get_to(g.gliderBGAReg);

	// Assuming dates are stored as UNIX timestamps (seconds since epoch)
	g.annualValidUntil = j.at("annualValidUntil").get<time_t>();
	g.arcValidUntil = j.at("arcValidUntil").get<time_t>();
	g.insuredUntil = j.at("insuredUntil").get<time_t>();
	g.nextWeighing = j.at("nextWeighing").get<time_t>();

	g.minutesInAir = j.at("minutesInAir").get<int>();
	g.winchLaunches = j.at("winchLaunches").get<int>();
	g.aerotowLaunches = j.at("aerotowLaunches").get<int>();
	g.totalLaunches = j.at("totalLaunches").get<int>();
}
