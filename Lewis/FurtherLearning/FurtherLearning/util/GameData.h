#pragma once
#include <memory>

class GameData
{
public:
	GameData();
	~GameData();
	static GameData* GetInstance();
private:
	static std::unique_ptr<GameData> s_Instance;
public:

private:

};