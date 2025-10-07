#pragma once
#include "../Stats/Gliders.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <ctime>

class StatRecorder {
public:
	StatRecorder();

	void AddGlider(Glider glider);
	GliderInfo& ReturnGliderInfo(std::string& gliderBGAReg);
	void PrintGliderInfo(GliderInfo& gliderInfo);
	void ChangeValue(GliderInfo& infoToModify);
private:
	void LoadFromFile(std::string& filePath);
	void SaveToFile(std::string& filePath);
	void PrintTime(time_t time);
	void ConvertMinutes(int minutes);

	void to_json(nlohmann::json& j, const GliderInfo& g);
public:

private:
	std::vector<Glider> gliders;
	char timeText[100];
	int minutesAndHours[2];
};