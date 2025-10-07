#pragma once
#include "../Stats/Gliders.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>

using json = nlohmann::json;

class StatRecorder {
public:
	StatRecorder();

	void AddGlider();
	GliderInfo* ReturnGliderInfo(std::string& gliderBGAReg);
	void PrintGliderInfo(GliderInfo& gliderInfo);
	void ChangeValue(GliderInfo& infoToModify);
private:
	int LoadFromFile(const std::string& filePath);
	void SaveToFile(const std::string& filePath);
	void PrintTime(time_t time);
	void ConvertMinutes(int minutes);
public:

private:
	std::vector<Glider> gliders;
	char timeText[100];
	int minutesAndHours[2];
};

