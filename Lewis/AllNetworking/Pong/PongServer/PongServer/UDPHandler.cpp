#include "UDPHandler.h"

UDPHandler::UDPHandler(std::string ip, int port) : sock(INVALID_SOCKET), serverIp(ip), serverPort(port), clientLength(sizeof(clientInfo)), userManager(sock)
{
	int wserr;
	
	WORD version = MAKEWORD(2, 2);
	wserr = WSAStartup(version, &data);

	if (wserr != 0) {
		std::cout << "ERROR LOADING WINSOCK DLL\n";
		return;
	}
	std::cout << "Winsock DLL loaded\n";

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == SOCKET_ERROR) {
		std::cout << "ERROR CREATING SOCKET: " << WSAGetLastError() << "\n";
		WSACleanup();
		return;
	}
	
	sockaddr_in serverInfo;
	serverInfo.sin_port = htons(port);
	serverInfo.sin_family = AF_INET;
	inet_pton(AF_INET, serverIp.c_str(), &serverInfo.sin_addr);
	if (bind(sock, (sockaddr*)&serverInfo, sizeof(serverInfo)) == SOCKET_ERROR) {
		std::cout << "ERROR BINDING THE SOCKET: " << WSAGetLastError() << "\n";
		WSACleanup();
		return;
	}

	userManager.SetSock(sock);

	std::cout << "Socket created and bound successfully\n";
}

UDPHandler::~UDPHandler()
{
	closesocket(sock);
	WSACleanup();
}

void UDPHandler::GetDataInSocket()
{
	sockaddr_in clientInfo;
	ZeroMemory(&clientInfo, clientLength);

	ZeroMemory(inBuf, 1024);
	int bytesIn = recvfrom(sock, inBuf, 1024, 0, (sockaddr*)&clientInfo, &clientLength);
	if (bytesIn < 0) {
		std::cout << "ERROR RECEIVING DATA\n";
		return;
	}
	char clientIp[INET_ADDRSTRLEN];
	ZeroMemory(clientIp, INET_ADDRSTRLEN);

	inet_ntop(AF_INET, &clientInfo.sin_addr, clientIp, INET_ADDRSTRLEN);

	switch (inBuf[0]) {
	case 0: ClientJoined(clientInfo); break;
	case 1: ClientLeft(clientInfo); break;
	case 3: ReceiveInput(inBuf, clientInfo); break;
	}
}

void UDPHandler::ClientJoined(sockaddr_in& clientInfo) {
	ZeroMemory(&outBuf, 1024);
	userManager.AddUser(clientInfo);
	sendto(sock, outBuf, 1, 0, (sockaddr*)&clientInfo, sizeof(clientInfo));
}

void UDPHandler::ClientLeft(sockaddr_in& clientInfo) {
	userManager.RemoveUser(clientInfo);
}

void UDPHandler::ReceiveInput(char* inBuf, sockaddr_in& clientInfo) {
	int action;
	int key;

	memcpy(&key, inBuf + 1, sizeof(int));
	memcpy(&action, inBuf + 1 + sizeof(int), sizeof(int));

	int userId = userManager.GetUserIDByIP(clientInfo);

	if (action == GLFW_PRESS) {
		BroadcastMovement({ userId, glm::vec2(0.0f, 1.0f) * 100.0f });
	}
	std::cout << "ACTION: " << action << " KEY: " << key << " USER:" << userId << "\n";
}

void UDPHandler::BroadcastMovement(Movement move) {
	ZeroMemory(&outBuf, 1024);
	outBuf[0] = 2;
	memcpy(outBuf + 1, (char*)&move, sizeof(Movement));
	userManager.SendToAllUsers(outBuf, 13);
}