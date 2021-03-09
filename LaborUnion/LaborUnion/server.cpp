#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>

#pragma comment(lib, "ws2_32")

#define PORT 5678
#define PACKET_SIZE 1024

int main()
{
#pragma region 변수들
	WSADATA		wsaData;
	SOCKET		sListening;
	SOCKET		sClient;
	SOCKADDR_IN clientData;
	SOCKADDR_IN serverData;
	{
		serverData.sin_addr.s_addr	= htonl(INADDR_ANY);
		serverData.sin_port			= htons(PORT);
		serverData.sin_family		= AF_INET;
	}
	INT			clientDataSize		= sizeof(clientData);
	CHAR		chMsg[PACKET_SIZE] = "와 서노 아시는구나\r\n";
#pragma endregion


	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bind(sListening,  (SOCKADDR*)&serverData, sizeof(serverData));
	listen(sListening, SOMAXCONN);
	
	sClient = accept(sListening, (SOCKADDR*)&clientData, &clientDataSize);
	closesocket(sListening);

	send(sClient, chMsg, PACKET_SIZE, 0);

	recv(sClient, chMsg, PACKET_SIZE, 0);
	printf("%s\r\n", chMsg);


	closesocket(sClient);
	WSACleanup();
	_getch();

	return(0);
}