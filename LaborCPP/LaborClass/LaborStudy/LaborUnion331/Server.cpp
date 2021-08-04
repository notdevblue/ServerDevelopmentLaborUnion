#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

int main()
{
	SOCKET sClient;
	SOCKET sListening;

	SOCKADDR_IN clientAddr;
	SOCKADDR_IN serverAddr;

	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(56789);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	bind(sListening, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	listen(sListening, SOMAXCONN);

	int clientSize = sizeof(clientAddr);
	sClient = accept(sListening, (SOCKADDR*)&clientAddr, &clientSize);

	char chMsg[1024] = "¿À¸®";
	send(sClient, chMsg, 1024, 0);

	closesocket(sClient);
	closesocket(sListening);
	WSACleanup();

	return(0);
}