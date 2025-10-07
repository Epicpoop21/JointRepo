#pragma once
#include <nlohmann/json.hpp>
#include <ctime>
#include <string>

struct GliderInfo {
	std::string gliderBGAReg;
	std::string gliderType;

	time_t annualValidUntil;
	time_t arcValidUntil;
	time_t insuredUntil;
	time_t nextWeighing;

	int minutesInAir;
	int winchLaunches;
	int aerotowLaunches;
};

class Glider
{
public:
	Glider() = default;
	Glider(GliderInfo info);
	~Glider();

private:

public:
	GliderInfo info;
private:
};

using json = nlohmann::json;

inline void to_json(nlohmann::json& j, const GliderInfo& info) {
	j = nlohmann::json{
		{"gliderType", info.gliderType},
		{"gliderBGAReg", info.gliderBGAReg},
		{"annualValidUntil", info.annualValidUntil},
		{"arcValidUntil", info.arcValidUntil},
		{"insuredUntil", info.insuredUntil},
		{"nextWeighing", info.nextWeighing},
		{"minutesInAir", info.minutesInAir},
		{"winchLaunches", info.winchLaunches},
		{"aerotowLaunches", info.aerotowLaunches}
	};
}

inline void from_json(const nlohmann::json& j, GliderInfo& info) {
	j.at("gliderType").get_to(info.gliderType);
	j.at("gliderBGAReg").get_to(info.gliderBGAReg);

	// Assuming dates are stored as UNIX timestamps (seconds since epoch)
	info.annualValidUntil = j.at("annualValidUntil").get<time_t>();
	info.arcValidUntil = j.at("arcValidUntil").get<time_t>();
	info.insuredUntil = j.at("insuredUntil").get<time_t>();
	info.nextWeighing = j.at("nextWeighing").get<time_t>();

	info.minutesInAir = j.at("minutesInAir").get<int>();
	info.winchLaunches = j.at("winchLaunches").get<int>();
	info.aerotowLaunches = j.at("aerotowLaunches").get<int>();
}

inline void to_json(json& j, const Glider& g) {
	j = json{ {"info", g.info} };
}

inline void from_json(const json& j, Glider& g) {
	j.at("info").get_to(g.info);
}
