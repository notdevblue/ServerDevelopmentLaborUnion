#include <WS2tcpip.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#pragma comment(lib, "ws2_32")

bool g_isDisconnected = false;
CRITICAL_SECTION crit;

DWORD WINAPI recvThread(LPVOID lpSocket)
{
	printf("msg recv thread running...\r\n");
	SOCKET socket = *(SOCKET*)lpSocket;

	CHAR chMsg[1024];

	COORD pos{ 0,3 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	while (!g_isDisconnected)
	{
		recv(socket, chMsg, 1024, 0);
		//system("cls");
		printf("%s", chMsg);
	}

	return(0);
}

int main()
{
	InitializeCriticalSection(&crit);

	HANDLE hRecv;
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN clientData;
	{
		clientData.sin_family = AF_INET;
		clientData.sin_port = htons(56789);
		InetPton(AF_INET, TEXT("127.0.0.1"), &clientData.sin_addr);
	}
	CHAR input[1];

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	connect(clientSocket, (SOCKADDR*)&clientData, sizeof(clientData));
	printf("connected.\r\n");
	printf("q 를 눌러 나가세요: ");
	hRecv = CreateThread(NULL, 0, recvThread, &clientSocket, 0, NULL);
	while ((input[0] = tolower(input[0] = _getch())) != 'q')
	{
		send(clientSocket, input, 1, 0);
	}
	g_isDisconnected = true;

	closesocket(clientSocket);

	WSACleanup();
	
	if (WaitForSingleObject(hRecv, INFINITE) != WAIT_OBJECT_0)
	{
		printf("오 이런,");
	}

	DeleteCriticalSection(&crit);
	return(0);
}