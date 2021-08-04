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

	clientNumber = 1;

	sClient = (SOCKET*)malloc(sizeof(SOCKET) * clientNumber);
#pragma region sClient 배열 검사
	if (sClient == NULL)
	{
		fprintf(stderr, "Error at CEasyServer.cpp Line: %d, cannot malloc", __LINE__);
	}
#pragma endregion

	hRecvThread = (HANDLE*)malloc(sizeof(HANDLE) * clientNumber);
#pragma region sClient 배열 검사
	if (hRecvThread == NULL)
	{
		fprintf(stderr, "Error at CEasyServer.cpp Line: %d, cannot malloc", __LINE__);
	}
#pragma endregion


	hSendThread = CreateThread(NULL, 0, senderThreadStart, (LPVOID)this, 0, NULL);
}

CEasyServer::~CEasyServer()
{
	free(sClient);
	free(hRecvThread);
	WSACleanup();
}
#pragma endregion

#pragma region 기능 함수

INT _Must_inspect_result_ _Check_return_ CEasyServer::acceptClient()
{
	SOCKET sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
#pragma region sListening 값 검사
	if (sListening == INVALID_SOCKET)
	{
		printf("Error at CEasyServer.cpp, Line: %d, cannot create listening socket. Error code: %d, ", __LINE__, WSAGetLastError()); return(-1);
	}
#pragma endregion

	bind(sListening, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	listen(sListening, SOMAXCONN);

#pragma region 배열 크기 증가
	
	// Socket
	SOCKET* sTempSockArr = (SOCKET*)realloc(sClient, sizeof(SOCKET) * clientNumber);
#pragma region sTempSockArr 배열 검사
	if (sTempSockArr == NULL)
	{
		fprintf(stderr, "Error at CEasyServer.cpp, Line: %d, cannot realloc", __LINE__); return(-1);
	}
#pragma endregion

	sClient = sTempSockArr;
#pragma region sTempSockArr 배열 삭제
	free(sTempSockArr);
	sTempSockArr = NULL;
#pragma endregion
	
	// Thread
	HANDLE* sTempThreadArr = (HANDLE*)realloc(hRecvThread, sizeof(HANDLE) * clientNumber);
#pragma region sTempThreadArr 배열 검사
	if (sTempThreadArr == NULL)
	{
		fprintf(stderr, "Error at CEasyServer.cpp, Line: %d, cannot realloc", __LINE__); return(-1);
	}
#pragma endregion
	hRecvThread = sTempThreadArr;

#pragma region sTempThreadArr 배열 삭제
	free(sTempThreadArr);
	sTempThreadArr = NULL;
#pragma endregion
#pragma endregion

	sClient[clientNumber - 1] = accept(sListening, (SOCKADDR*)&clientAddr, &clientSize);
#pragma region sClient 값 검사
	if (sClient[clientNumber] == INVALID_SOCKET)
	{
		printf("Error at CEasyServer.cpp, Line: %d, client socket invalid. Error code: %d, ", __LINE__ - 1, WSAGetLastError()); return(-1);
	}
#pragma endregion
	closesocket(sListening);


	//hRecvThread[clientNumber - 1] = CreateThread(NULL, 0, recvThreadStart, (sClient + clientNumber - 1), 0, NULL);
	hRecvThread[clientNumber - 1] = CreateThread(NULL, 0, recvThreadStart, (LPVOID)this, 0, NULL);

	++clientNumber;
	return(0);
}

INT _Must_inspect_result_ _Check_return_ CEasyServer::waitSenderThread()
{
	return WaitForSingleObject(hSendThread, INFINITE);
}
#pragma endregion

#pragma region Thread

DWORD CEasyServer::recvThread(LPVOID lpParam)
{
	CRITICAL_SECTION crit;
	SOCKET sClient = *(SOCKET*)lpParam;
	CHAR chBuffer[PACKET_SIZE];


	while (recv(sClient, chBuffer, PACKET_SIZE, 0))
	{
		CRAIICriticalSession raiiCritcal(crit);
		m_msgQueue.push(chBuffer);
	}

	closesocket(sClient);
}

DWORD CEasyServer::msgSenderThread()
{
	CRITICAL_SECTION crit;

	while (true)
	{
		CRAIICriticalSession raiiCritical(crit);
		if (!m_msgQueue.empty())
		{
			for (int i = 0; i < clientNumber; ++i)
			{
				send(sClient[i], m_msgQueue.front(), PACKET_SIZE, 0);
			}
			m_msgQueue.pop();
		}
	}
}
#pragma endregion