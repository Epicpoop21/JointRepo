#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <string>
#include <iostream>

#include <glm/glm.hpp>

class Game;

struct Movement {
	int objectId;
	glm::vec2 velocity;
};

enum class DataCode : uint8_t {
	CLIENT_JOIN = 0,
	CLIENT_LEAVE = 1,
	CLIENT_UPDATE = 2,
	CLIENT_INPUT = 3,
	PAUSE = 4
};

class UDPHandler
{
public:
	UDPHandler(std::string serverIp, int port);
	~UDPHandler();

	void RecieveServerReply();
	void DealWithMovement();
	void SendInput(int action, int key);
	void GetDataFromServer();
	void SetGame(Game* game);
private:

public:

private:
	WSADATA data;
	SOCKET sock;
	int serverPort;
	std::string serverIp;
	char inBuf[1024];
	char outBuf[1024];

	sockaddr_in serverInfo;
	int serverLength;

	sockaddr_in clientInfo;
	int clientLength;

	fd_set set;

	Game* game;
};

