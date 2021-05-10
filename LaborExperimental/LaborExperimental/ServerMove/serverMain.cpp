#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

CHAR chMsg[1];

short g_posX = 0;
short g_posY = 0;

void move(char input);

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKADDR_IN serverData;
	{
		serverData.sin_family = AF_INET;
		serverData.sin_port = htons(56789);
		serverData.sin_addr.s_addr = INADDR_ANY;
	}
	SOCKET sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bind(sListening, (SOCKADDR*)&serverData, sizeof(serverData));

	listen(sListening, SOMAXCONN);
	printf("server is listening...\r\n");

	SOCKADDR_IN clientData;
	INT clientDataSize = sizeof(clientData);
	SOCKET sClient = accept(sListening, (SOCKADDR*)&clientData, &clientDataSize);
	closesocket(sListening);
	printf("client connected\r\n");

	while (true)
	{
		int buffer = recv(sClient, chMsg, 1, 0);
		if (!buffer || buffer == -1)
			break;

		system("cls");
		move(chMsg[0]);
	}


	closesocket(sClient);
	printf("\r\ndisconnected\r\n");
	WSACleanup();

	return(0);
}

void move(char input)
{
	switch (input)
	{
	case 'w':
		if (g_posY - 1 >= 0)
		{
			--g_posY;
		}
		break;

	case 's':
		++g_posY;
		break;

	case 'a':
		if (g_posX - 1 >= 0)
		{
			--g_posX;
		}
		break;

	case 'd':
		++g_posX;
		break;

	default:
		break;
	}

	COORD pos{ g_posX, g_posY };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	printf("0");
}