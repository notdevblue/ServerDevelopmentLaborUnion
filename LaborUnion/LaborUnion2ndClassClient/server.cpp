#include <WS2tcpip.h>
#include <iostream>
#include <conio.h>
#pragma comment(lib, "ws2_32")

DWORD WINAPI ThreadProc(LPVOID lpParam);

SOCKET sClient;
char chRecvMsg[1024];
bool isDisconnected = false;


int main()
{
	WSADATA wsaData;

	SOCKET sListening;
	SOCKADDR_IN serverAddr;
	{
		serverAddr.sin_port = htons(56789);
		serverAddr.sin_family = AF_INET;
		//InetPton(AF_INET, TEXT("127.0.0.1"), &serverAddr.sin_addr);
		serverAddr.sin_addr.s_addr = INADDR_ANY;
	}

	
	SOCKADDR_IN clientAddr;
	int clientAddrSize = sizeof(clientAddr);
	char chSendMsg[1024];
	
	//HANDLE hThread;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sListening, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	std::cout << "연결 기다리는 중." << std::endl;
	listen(sListening, SOMAXCONN);

	sClient = accept(sListening, (SOCKADDR*)&clientAddr, &clientAddrSize);
	closesocket(sListening);
	std::cout << "연결 성공." << std::endl;

	CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);


	while (!isDisconnected)
	{
		std::cin.getline(chSendMsg, 1024);
		send(sClient, chSendMsg, 1024, 0);
	}

	_getch();

	closesocket(sClient);
	WSACleanup();
	
	return(0);
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	while (recv(sClient, chRecvMsg, 1024, 0) != -1)
	{
		printf("누군가: %s\r\n", chRecvMsg);
	}
	isDisconnected = true;

	return(0);
}