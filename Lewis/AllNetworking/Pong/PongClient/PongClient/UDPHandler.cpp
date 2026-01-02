#include "UDPHandler.h"
#include "./game/Game.h"

UDPHandler::UDPHandler(std::string ip, int port) : sock(INVALID_SOCKET), serverIp(ip), serverPort(port), clientLength(sizeof(clientInfo)), serverLength(sizeof(serverInfo))
{
	std::cout << "sizeof(Movement) = " << sizeof(Movement) << "\n";
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

	clientInfo.sin_family = AF_INET;
	clientInfo.sin_port = htons(0);
	clientInfo.sin_addr.S_un.S_addr = ADDR_ANY;

	if (bind(sock, (sockaddr*)&clientInfo, clientLength) == SOCKET_ERROR) {
		std::cout << "ERROR BINDING SOCKET " << WSAGetLastError() << "\n";
		WSACleanup();
		return;
	}
	else {
		std::cout << "Binded socket\n";
	}
	

	serverInfo.sin_port = htons(port);
	serverInfo.sin_family = AF_INET;
	inet_pton(AF_INET, serverIp.c_str(), &serverInfo.sin_addr);

	ZeroMemory(outBuf, 1024);
	outBuf[0] = 0;

	sendto(sock, outBuf, 1, 0, (sockaddr*)&serverInfo, serverLength);
}

UDPHandler::~UDPHandler()
{
	ZeroMemory(outBuf, 1024);
	outBuf[0] = 1;
	sendto(sock, outBuf, 1, 0, (sockaddr*)&serverInfo, serverLength);
	closesocket(sock);
	WSACleanup();
}

void UDPHandler::RecieveServerReply()
{
	std::cout << "Client connected to server\n";
}

void UDPHandler::DealWithMovement()
{
	Movement move;
	ZeroMemory(&move, sizeof(Movement));
	memcpy(&move, inBuf + 1, sizeof(Movement));
	std::cout << move.objectId << "\n";
	std::cout << "X: " << move.velocity.x << " Y: " << move.velocity.y << "\n";

	Object* object = Object::GetObjectByID(move.objectId);
	if (object == nullptr) return;
	object->Move(move.velocity);
}

void UDPHandler::SendInput(int action, int key)
{
	ZeroMemory(outBuf, 1024);
	outBuf[0] = 3;
	memcpy(outBuf + 1, &key, sizeof(int));
	memcpy(outBuf + 1 + sizeof(int), &action, sizeof(int));

	sendto(sock, outBuf, 9, 0, (sockaddr*)&serverInfo, serverLength);
}

void UDPHandler::SetGame(Game* game)
{
	this->game = game;
}

void UDPHandler::GetDataFromServer()
{
	ZeroMemory(inBuf, 1024);

	FD_ZERO(&set);
	FD_SET(sock, &set);

	timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 10000; // non-blocking poll

	int result = select(0, &set, nullptr, nullptr, &timeout);
	if (result == SOCKET_ERROR) {
		std::cout << "ERROR READING FROM SOCKET: " << WSAGetLastError() << "\n";
	}
	else if (result > 0) {
		int bytesIn = recvfrom(sock, inBuf, 1024, 0, nullptr, nullptr);
		/*std::cout << bytesIn << " BYTES RECIEVED\n";
		for (int i = 0; i < bytesIn; i++) {
			std::cout << "Byte[" << i << "] = " << (int)(unsigned char)inBuf[i] << "\n";
		}*/
		if (bytesIn > 0) {
			switch (inBuf[0]) {
			case 0: RecieveServerReply();
			case 2: DealWithMovement();  break;
			}
		}
	}
}

