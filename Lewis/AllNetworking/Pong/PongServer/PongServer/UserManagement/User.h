#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>

#include <string>
#include <iostream>

#include "InputTracker.h"

class User {
public:
	User(sockaddr_in& clientIn, int userId);
	~User();
private:

public:
	char ipBuf[INET_ADDRSTRLEN];
	sockaddr_in clientInfo;
	InputTracker inputTracker;
private:
	int userId;
};