#include "User.h"

User::User(sockaddr_in& clientIn, int userId) : clientInfo(clientIn), userId(userId), inputTracker(userId)
{
	inet_ntop(AF_INET, &clientIn.sin_addr, ipBuf, INET_ADDRSTRLEN);
}

User::~User() {

}