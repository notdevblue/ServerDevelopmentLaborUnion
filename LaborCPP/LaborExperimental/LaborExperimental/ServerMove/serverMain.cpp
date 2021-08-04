#include <WS2tcpip.h>
#include <Windows.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

short g_posX = 0;
short g_posY = 0;
bool g_isDisconnected = false;

void move(char input);

DWORD WINAPI sendThread(LPVOID socket)
{
	SOCKET sendSocket = *(SOCKET*)socket;

	COORD pos{ 10, 5 };
	CHAR msg[1024];

	while (!g_isDisconnected)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		//system("cls");
		scanf_s("%[^\n]s", msg, 1024);
		send(sendSocket, msg, 1024, 0);

	}

	return(0);
}

int main()
{
	
	HANDLE hSend;

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

	hSend = CreateThread(NULL, 0, sendThread, &sClient, 0, NULL);
	CHAR chMsg[1];
	while (true)
	{
		int buffer = recv(sClient, chMsg, 1, 0);
		if (!buffer || buffer == -1)
		{
			break;
		}
		
		move(chMsg[0]);
	}
	g_isDisconnected = true;

	closesocket(sClient);
	printf("\r\ndisconnected\r\n");
	WSACleanup();

	if (WaitForSingleObject(hSend, INFINITE) != WAIT_OBJECT_0)
	{
		printf("¿ÀÀÌ·±\r\n");
	}

	return(0);
}

void move(char input)
{
	int befX = g_posX;
	int befY = g_posY;

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



	COORD befPos{ befX, befY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), befPos);
	printf(" ");
	COORD newPos{ g_posX, g_posY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), newPos);
	printf("0");
}