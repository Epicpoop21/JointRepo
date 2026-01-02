#include "stdafx.h"

int SetupDLL();
SOCKET CreateSocket();
int BindSocket(SOCKET socket, const std::string& ip, unsigned int port);
int MakeSocketListen(SOCKET socket, unsigned int maxConnections);
SOCKET AcceptSocket(SOCKET listenSocket);

int main() {
	SOCKET serverSocket;
	unsigned int port = 55555;

	if (SetupDLL() != 0) return -1;

	serverSocket = CreateSocket();
	if (serverSocket == INVALID_SOCKET) return -1;

	if (BindSocket(serverSocket, "0.0.0.0", 55555) != 0) return -1;
	if (MakeSocketListen(serverSocket, 1) != 0) return -1;
	
	fd_set master;
	FD_ZERO(&master);
	
	FD_SET(serverSocket, &master);

	std::unordered_map<SOCKET, int> personNumberMap;
	int personNum = 0;
	char inBuf[4096];
	while (true) {
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; socketCount > i; i++) {
			SOCKET sock = copy.fd_array[i];
			if (sock == serverSocket) {
				SOCKET client = AcceptSocket(serverSocket);
				FD_SET(client, &master);

				personNum++;
				personNumberMap[client] = personNum;

				std::string welcomeMessage = "Welcome to the server! You are person " + std::to_string(personNum) + "! \n\r";
				send(client, welcomeMessage.c_str(), welcomeMessage.size(), 0);
			}
			else {
				ZeroMemory(inBuf, 4096);

				int bytesRecieved = recv(sock, inBuf, 4096, 0);
				if (bytesRecieved <= 0) {
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else {
					while (bytesRecieved > 0 &&
						(inBuf[bytesRecieved - 1] == '\n' ||
							inBuf[bytesRecieved - 1] == '\r')) {
						inBuf[--bytesRecieved] = '\0';
					}
					for (int i = 0; i < master.fd_count; i++) {
						SOCKET outSock = master.fd_array[i];
						if (outSock != serverSocket && outSock != sock) {
							int numOfPerson = personNumberMap[sock];
							std::string outText = "Person " + std::to_string(numOfPerson) + ": " + inBuf + "\n\r";

							send(outSock, outText.c_str(), outText.size(), 0);
						}
					}
				}
			}
		}
	}

	return 0;
}



int SetupDLL() {
	WSADATA wsaData;
	int wsaerr;

	WORD wVersionRequested = MAKEWORD(2, 2);
	wsaerr = WSAStartup(wVersionRequested, &wsaData);
	if (wsaerr != 0) {
		std::cout << "Winsock DLL not found\n";
		return -1;
	}
	else {
		std::cout << "Winsock DLL found\n";
		std::cout << "Status: " << wsaData.szSystemStatus << "\n";
		return 0;
	}
}

SOCKET CreateSocket() {
	SOCKET serverSocket;
	serverSocket = INVALID_SOCKET;
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (serverSocket == INVALID_SOCKET) {
		std::cout << "Error at socket(): " << WSAGetLastError() << "\n";
		WSACleanup();
		return INVALID_SOCKET;
	}
	else {
		std::cout << "Socket created\n";
	}
	return serverSocket;
}

int BindSocket(SOCKET socket, const std::string& ip, unsigned int port)
{
	sockaddr_in service;
	service.sin_family = AF_INET;
	//inet_pton(AF_INET, ip.c_str(), &service.sin_addr);
	service.sin_port = htons(port);
	service.sin_addr.s_addr = INADDR_ANY;
	if (bind(socket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR) {
		std::cout << "Bind failed: " << WSAGetLastError() << "\n";
		WSACleanup();
		return -1;
	}
	else {
		char addressBuff[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &service.sin_addr, addressBuff, sizeof(addressBuff));
		std::cout << "Correctly binded\n";
		std::cout << "SERVER IP: " << addressBuff << "\n";
		std::cout << "SERVER PORT: " << service.sin_port << "\n";
		return 0;
	}
}

int MakeSocketListen(SOCKET socket, unsigned int maxConnections)
{
	if (listen(socket, maxConnections) == SOCKET_ERROR) {
		std::cout << "Listen failed: " << WSAGetLastError() << "\n";
		return -1;
	}
	else {
		std::cout << "Started listening\n";
		return 0;
	}
}

SOCKET AcceptSocket(SOCKET listenSocket)
{
	sockaddr_in clientInfo;
	int clientSize = sizeof(clientInfo);

	SOCKET acceptSocket = INVALID_SOCKET;
	acceptSocket = accept(listenSocket, (sockaddr*)&clientInfo, &clientSize);
	if (acceptSocket == INVALID_SOCKET) {
		std::cout << "Accept failed: " << WSAGetLastError() << "\n";
		WSACleanup();
		return -1;
	}
	else {
		char addressBuff[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &clientInfo.sin_addr, addressBuff, sizeof(addressBuff));
		std::cout << "Accepted connection\n";
		std::cout << "CLIENT IP: " << addressBuff << "\n";
		std::cout << "CLIENT PORT: " << clientInfo.sin_port << "\n";
		return acceptSocket;
	}
}



/*
	char buff[4096];

	while (true) {
		ZeroMemory(buff, 4096);

		int bytesRecieved = recv(acceptSocket, buff, sizeof(buff) - 1, 0);
		if (bytesRecieved == 0) {
			std::cout << "CLIENT DISCONNECTED \n";
			break;
		}
		else if (bytesRecieved > 0) {
			std::cout << "BYTES RECIEVED: " << bytesRecieved << "\n";
			std::cout << "MESSAGE RECIEVED: " << buff << "\n";
			int bytesSent = send(acceptSocket, buff, bytesRecieved + 1, 0);
		}
	} */