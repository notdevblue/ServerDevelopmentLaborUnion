#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>

#pragma comment(lib, "ws2_32");

int main()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		return -1;
	}

	SOCKET sListening;
	SOCKADDR_IN serverAddr;
	{
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(56789);
		serverAddr.sin_family = AF_INET;
	}

	sListening = socket(serverAddr.sin_family, SOCK_STREAM, IPPROTO_TCP);
	bind(sListening, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	listen(sListening, SOMAXCONN);

	SOCKET sClient;
	SOCKADDR_IN clientAddr;
	INT clientSize = sizeof(clientAddr);

	sClient = accept(sListening, (SOCKADDR*)&clientAddr, &clientSize);
	if (sClient == INVALID_SOCKET)
	{
		return -1;
	}

	send(sClient, "Hello this is server written with C", 36, 0);	


	closesocket(sListening);
	closesocket(sClient);
	WSACleanup();
	return 0;
}