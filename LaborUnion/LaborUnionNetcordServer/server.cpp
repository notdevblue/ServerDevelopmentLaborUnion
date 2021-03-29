#include <iostream>

#define NOTUSING
#define ONE2N

#ifdef NOTUSING
#ifdef ONE2N
#undef ONE2N
#endif

int main()
{
	std::cout << "사용하지 않는 파일입니다." << std::endl;

	return(0);
}

#endif




#ifdef ONE2N // 서버를 통한 1ㄷN 통신 구현

#include <WS2tcpip.h>
#include <stdio.h>
#include <queue>
#pragma comment(lib, "ws2_32")


DWORD WINAPI ConnectionThread(LPVOID lpParam);
DWORD WINAPI RecvThread(LPVOID lpParam);

std::queue<LPSTR> g_msgQueue;


int main()
{
	WSADATA	wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#pragma region 채팅 방 크기
	UINT	roomSize = -1;
	printf("몇 명과 체팅할까요?: ");
	while (true)
	{
		roomSize = -1;
		scanf_s("%d", &roomSize);
		if (roomSize >= 10)
		{
			printf("아니 얼마나 입력한거에요;;\r\n");
			continue;
		}
		break;
	}
	printf("%d 명이 접속할 수 있는 체팅 서버를 만듭니다\r\n", roomSize);
#pragma endregion

	HANDLE* hThread = new HANDLE[roomSize];

	for (UINT i = 0; i < roomSize; ++i)
	{
		hThread[i] = CreateThread(NULL, 0, ConnectionThread, NULL, 0, NULL);
	}

	WaitForMultipleObjects(roomSize, hThread, true, INFINITE);


	WSACleanup();
	return(0);
}

// 나중을 위한 주석
// while(true)로 무한루프 걸고
// 그 안에 socket, bind, listen, accept 까지 한 다음 CreateThread
// 그리고 다시 처음으로 돌아감
// while 문 처음에 변수선언하면 컴퓨터가 가능한 안에서 무한으로 접속 가능

DWORD WINAPI ConnectionThread(LPVOID lpParam)
{
	SOCKET		sListening;
	SOCKET		sClient;
	SOCKADDR_IN	serverAddr;
	SOCKADDR_IN	clientAddr;
	INT			clientAddrSize = sizeof(clientAddr);
	
	CRITICAL_SECTION crit;
	InitializeCriticalSection(&crit);

	serverAddr; // 보기 편하게 하기 위함
	{
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(5678);
		serverAddr.sin_family = AF_INET;
	}
	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sListening, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
	listen(sListening, SOMAXCONN);
	sClient = accept(sListening, (SOCKADDR*)&clientAddr, &clientAddrSize); // ERROR: WSAEINVAL 10022
	if (sClient == INVALID_SOCKET)
	{
		printf("%x", WSAGetLastError());
		return(0);
	}
	closesocket(sListening);

	CreateThread(NULL, 0, RecvThread, &sClient, 0, NULL);

	while (true)
	{
		EnterCriticalSection(&crit);
		if (g_msgQueue.size() != 0)
		{
			send(sClient, g_msgQueue.front(), 1024, 0);
			g_msgQueue.pop();
		}
		LeaveCriticalSection(&crit);
	}

	closesocket(sClient);
	DeleteCriticalSection(&crit);
	return 0;
}

DWORD WINAPI RecvThread(LPVOID lpParam)
{
	SOCKET sClient = *(SOCKET*)lpParam;
	CHAR chMsg[1024];

	CRITICAL_SECTION crit;
	InitializeCriticalSection(&crit);
	while (recv(sClient, chMsg, 1024, 0) != -1)
	{
		printf("%s\r\n", chMsg);
		EnterCriticalSection(&crit);
		g_msgQueue.push(chMsg);
		LeaveCriticalSection(&crit);
	}
	DeleteCriticalSection(&crit);

	return 0;
}
#endif