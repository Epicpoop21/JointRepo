#include "UserManager.h"

#include <iostream>

#include <WinSock2.h>
#include <WS2tcpip.h>

UserManager::UserManager(SOCKET serverSocket) : nextUserNumber(0), sock(serverSocket)
{

}

UserManager::~UserManager() 
{

}

int UserManager::GetUserIDByIP(sockaddr_in& clientInfo) 
{
	for (auto const& user : userIdMap) {
		if (user.second.clientInfo.sin_addr.S_un.S_addr == clientInfo.sin_addr.S_un.S_addr && user.second.clientInfo.sin_port == clientInfo.sin_port) {
			return user.first;
		}
	}
}

int UserManager::GetUserIDByIP(char* buf, short port)
{
	sockaddr_in ipAddress;
	ipAddress.sin_family = AF_INET;
	ipAddress.sin_port = htons(port);

	if (buf[sizeof(buf) - 1] != '\0') {
		std::cout << "STRING IS NOT NULL TERMINATED\n";
		return -1;
	}
	inet_pton(AF_INET, buf, &ipAddress);
	return GetUserIDByIP(ipAddress);
}

void UserManager::SendToAllUsers(char* data, unsigned int numOfBytes) {
	for (auto const& user : userIdMap) {
		sendto(sock, data, numOfBytes, 0, (sockaddr*)&user.second.clientInfo, sizeof(user.second.clientInfo));
	}
}

void UserManager::SetSock(SOCKET sock) {
	this->sock = sock;
}

void UserManager::AddUser(sockaddr_in& clientInfo) 
{
	auto [it, inserted] = userIdMap.emplace(nextUserNumber, User(clientInfo, nextUserNumber));
	std::cout << "ADDED USER " << it->second.ipBuf << ":" << htons(clientInfo.sin_port) << "\n";
	nextUserNumber++;
}

void UserManager::RemoveUser(sockaddr_in& clientInfo)
{
	int userId = GetUserIDByIP(clientInfo);
	if (userId == -1) {
		std::cout << "Couldn't remove user";
		return;
	}
	auto it = userIdMap.find(userId);
	std::cout << "REMOVED USER " << it->second.ipBuf << ":" << htons(clientInfo.sin_port) << "\n";
	if (it != userIdMap.end()) {
		userIdMap.erase(it);
	}
}