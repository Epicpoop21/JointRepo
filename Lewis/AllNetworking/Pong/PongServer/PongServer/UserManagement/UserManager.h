#pragma once

#include <map>

#include "User.h"
#include "../Objects/Object.h"
#include "../Objects/Paddle.h"
#include "../Objects/Ball.h"

class UserManager {
public:
	UserManager(SOCKET serverSocket);
	~UserManager();

	int GetUserIDByIP(sockaddr_in& clientInfo);
	int GetUserIDByIP(char* buf, short port);

	void SendToAllUsers(char* data, unsigned int numOfBytes);
	void SetSock(SOCKET sock);

	void AddUser(sockaddr_in& clientInfo);
	void RemoveUser(sockaddr_in& clientInfo);

	void MoveObjects();
private:

public:
	std::map<unsigned int, User> userIdMap;

	Paddle* lPaddle;
	Paddle* rPaddle;
	Ball* ball;
private:
	int nextUserNumber;
	SOCKET sock;
};