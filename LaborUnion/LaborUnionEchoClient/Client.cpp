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
	SOCKET		sClient;
	SOCKADDR_IN clientData;
	{
		InetPton(AF_INET, TEXT("127.0.0.1"), &clientData.sin_addr.s_addr);
		clientData.sin_port = htons(PORT);
		clientData.sin_family = AF_INET;
	}
	CHAR		chMsg[PACKET_SIZE];
#pragma endregion

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("Error at line %d\r\n", __LINE__);
		return(-1);
	}

	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sClient == INVALID_SOCKET)
	{
		printf("Error at socket %x, line %d", WSAGetLastError(), __LINE__);
		return(-1);
	}

	if (connect(sClient, (SOCKADDR*)&clientData, sizeof(clientData)))
	{
		printf("Connection error %x, line %d", WSAGetLastError(), __LINE__);
		return(-1);
	}

	printf("Connected to Server.\r\n");

	while (gets_s(chMsg)) // Ctrl + Z 로 중지할 수 있음.
	{
		send(sClient, chMsg, PACKET_SIZE, 0);
		recv(sClient, chMsg, PACKET_SIZE, 0);
		printf("Server: %s\r\n", chMsg);
	}

	closesocket(sClient);
	WSACleanup();

	printf("Disconnected\r\n");
	printf("Press any key to continue...\r\n");
	_getch();

	return(0);
}