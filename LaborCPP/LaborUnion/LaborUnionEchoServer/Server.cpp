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
		serverData.sin_addr.s_addr = htonl(INADDR_ANY);
		serverData.sin_port = htons(PORT);
		serverData.sin_family = AF_INET;
	}
	INT			clientDataSize = sizeof(clientData);
	CHAR		chMsg[PACKET_SIZE] = "와 서노 아시는구나\r\n";
#pragma endregion

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("Error at line %d\r\n", __LINE__);
		return(-1);
	}

	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sListening == INVALID_SOCKET)
	{
		printf("Error at socket %x, line %d", WSAGetLastError(), __LINE__);
		return(-1);
	}

	bind(sListening, (SOCKADDR*)&serverData, sizeof(serverData));
	listen(sListening, SOMAXCONN);

	sClient = accept(sListening, (SOCKADDR*)&clientData, &clientDataSize);
	if (sClient == INVALID_SOCKET)
	{
		printf("Error at client socket %x, line %d", WSAGetLastError(), __LINE__);
		return(-1);
	}

	closesocket(sListening);
	printf("Client Connected.\r\n");

	while (recv(sClient, chMsg, PACKET_SIZE, 0) != -1)
	{
		printf("Client: %s\r\n", chMsg);
		send(sClient, chMsg, PACKET_SIZE, 0);
	}

	closesocket(sClient);
	WSACleanup();

	printf("Client disconnected.\r\n");
	printf("Press any key to continue...\r\n");
	_getch();

	return(0);
}