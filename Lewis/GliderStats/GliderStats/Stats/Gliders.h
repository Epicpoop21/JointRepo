#pragma once
#include <ctime>
#include <string>

struct GliderInfo {
	std::string gliderType;
	std::string gliderBGAReg;

	time_t annualValidUntil;
	time_t arcValidUntil;
	time_t insuredUntil;
	time_t nextWeighing;

	int minutesInAir;
	int winchLaunches;
	int aerotowLaunches;
	int totalLaunches;
};

class Glider
{
public:
	Glider(GliderInfo info);
	~Glider();

private:

public:
	GliderInfo info;
private:
};

