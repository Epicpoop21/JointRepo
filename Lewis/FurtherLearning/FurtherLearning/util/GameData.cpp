#include "GameData.h"

std::unique_ptr<GameData> GameData::s_Instance = nullptr;
GameData::GameData()
{
}

GameData::~GameData()
{
}

GameData* GameData::GetInstance() {
	if (!s_Instance) {
		s_Instance = std::make_unique<GameData>();
	}
	return s_Instance.get();
}