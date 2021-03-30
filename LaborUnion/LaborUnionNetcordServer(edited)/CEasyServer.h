#pragma once
#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

class CEasyServer
{
private:
	SOCKET* sClient;
	SOCKADDR_IN* clientAddr;
	SOCKADDR_IN serverAddr;
	WSADATA wsaData;

public:
	CEasyServer();
	~CEasyServer();

	void ListenClient();

};

