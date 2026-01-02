#include "stdafx.h"

int main() {
	SOCKET clientSocket;
	WSADATA wsaData;
	int wsaerr;
	int port = 55555;

	WORD wsaVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wsaVersionRequested, &wsaData);
	if (wsaerr != 0) {
		std::cout << "Error loading WinSock DLL\n";
		return -1;
	}
	else {
		std::cout << "Loaded winsock DLL\n";
		std::cout << "Status: " << wsaData.szSystemStatus << "\n";
	}

	clientSocket = INVALID_SOCKET;
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == INVALID_SOCKET) {
		std::cout << "Error creating socket: " << WSAGetLastError() << "\n";
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "Socket created\n";
	}

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &clientService.sin_addr);
	clientService.sin_port = htons(port);
	if (connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
		std::cout << "Error connecting to server: " << WSAGetLastError() << "\n";
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "Client connected\n";
	}
	char buff[200];
	Sleep(2000);

	int bc = recv(clientSocket, buff, 18, 0);
	if (bc == 0) {
		std::cout << "ERROR RECEIVING DATA\n";
	}
	else {
		std::cout << buff << "\n";
	}

	std::cout << "BYTE COUNT IS: " << bc << "\n";
	system("pause");
	return 0;
}