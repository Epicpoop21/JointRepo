#pragma once

#include <map>
#include "User.h"

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
private:

public:
	std::map<unsigned int, User> userIdMap;
private:
	int nextUserNumber;
	SOCKET sock;
};