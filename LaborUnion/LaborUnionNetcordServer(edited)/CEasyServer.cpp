#include "CEasyServer.h"

#pragma region 생성자 소멸자
CEasyServer::CEasyServer()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("Cannot inti winsock\r\n");
	}

	serverAddr;
	{
		serverAddr.sin_addr.s_addr	= INADDR_ANY;
		serverAddr.sin_port			= htons(56789);
		serverAddr.sin_family		= AF_INET;
	}

	clientNumber == 1;

	sClient = (SOCKET*)malloc(sizeof(SOCKET) * clientNumber);
#pragma region sClient 배열 검사
	if (sClient == NULL)
	{
		fprintf(stderr, "Error at CEasyServer.cpp Line: %d, cannot malloc", __LINE__ - 1);
	}
#pragma endregion
}

CEasyServer::~CEasyServer()
{
	free(sClient);
	WSACleanup();
}
#pragma endregion

INT CEasyServer::acceptClient()
{
	SOCKET sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#pragma region sListening 값 검사
	if (sListening == INVALID_SOCKET)
	{
		printf("Error at CEasyServer.cpp, Line: %d, cannot create listening socket. Error code: %d, ", __LINE__ - 1, WSAGetLastError()); return(-1);
	}
#pragma endregion

	bind(sListening, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	listen(sListening, SOMAXCONN);

	SOCKET* sTemp = (SOCKET*)realloc(sClient, sizeof(SOCKET) * clientNumber);
#pragma region sTemp 배열 검사
	if (sTemp == NULL)
	{
		fprintf(stderr, "Error at CEasyServer.cpp, Line: %d, cannot realloc", __LINE__ - 1); return(-1);
	}
#pragma endregion

	sClient = sTemp;

#pragma region sTemp 배열 삭제
	free(sTemp);
	sTemp = NULL;
#pragma endregion

	sClient[clientNumber - 1] = accept(sListening, (SOCKADDR*)&clientAddr, &clientSize);
#pragma region sClient 값 검사
	if (sClient[clientNumber] == INVALID_SOCKET)
	{
		printf("Error at CEasyServer.cpp, Line: %d, client socket invalid. Error code: %d, ", __LINE__ - 1, WSAGetLastError()); return(-1);
	}
#pragma endregion
	++clientNumber;

	closesocket(sListening);
}