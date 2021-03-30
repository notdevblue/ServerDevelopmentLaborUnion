#include "CEasyServer.h"

CEasyServer::CEasyServer()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("Cannot inti winsock\r\n");
	}

	serverAddr.sin_addr.s_addr = INADDR_ANY;
	serverAddr.sin_port = htons(56789);
	serverAddr.sin_family = AF_INET;

}

CEasyServer::~CEasyServer()
{
	WSACleanup();
}