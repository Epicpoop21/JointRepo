#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include <iostream>

#include "./UserManagement/UserManager.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

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
	void GetDataInSocket();
	void BroadcastMovement(Movement move);
private:
	void ReceiveInput(char* buf, sockaddr_in& clientInfo);
	void ClientJoined(sockaddr_in& clientInfo);
	void ClientLeft(sockaddr_in& clientInfo);
public:
	UserManager userManager;
private:
	WSADATA data;
	SOCKET sock;
	int serverPort;
	std::string serverIp;
	char inBuf[1024];
	char outBuf[1024];

	sockaddr_in clientInfo;
	int clientLength;

	fd_set set;
};

