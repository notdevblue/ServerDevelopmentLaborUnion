#pragma once
#include <WS2tcpip.h>
#include "CRAIICriticalSession.h"
#include <stdio.h>
#include <queue>

#pragma comment(lib, "ws2_32")



class CEasyServer
{
private:
#pragma region Client
	SOCKET*			sClient;
	SOCKADDR_IN*	clientAddr;
	INT				clientSize;
#pragma endregion

#pragma region Server
	SOCKADDR_IN		serverAddr;
	WSADATA			wsaData;
	INT				clientNumber;
#pragma endregion

#pragma region Thread
	HANDLE*			hRecvThread;
	HANDLE			hSendThread;
#pragma endregion

#pragma region Data
	std::queue<CHAR[PACKET_SIZE]> m_msgQueue;
#pragma endregion

public:
	CONSTRUCTOR CEasyServer();
	DESTRUCTOR	~CEasyServer();

	/// <summary>
	/// while(true) 로 돌리면 접속이 있을 때 마다 쓰레드를 만듭니다.
	/// </summary>
	/// <returns>에러가 있을 시 -1, 정상종료 시 0</returns>
	INT _Must_inspect_result_ _Check_return_ acceptClient();
	INT _Must_inspect_result_ _Check_return_ waitSenderThread(); //사용 안함

#pragma region Threads

#pragma region static
	inline static DWORD WINAPI senderThreadStart(LPVOID lpParam)
	{
		CEasyServer* This = (CEasyServer*)lpParam;
		return This->msgSenderThread();
	}
	inline static DWORD WINAPI recvThreadStart(LPVOID lpParam)
	{
		CEasyServer* This = (CEasyServer*)lpParam;
		return This->recvThread(sClient + clientNumber - 1);
	}
#pragma endregion

	


	DWORD msgSenderThread();
	DWORD recvThread(LPVOID lpParam);
#pragma endregion 
};