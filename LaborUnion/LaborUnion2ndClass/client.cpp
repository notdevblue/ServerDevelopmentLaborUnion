#include <WS2tcpip.h>
#include <iostream>
#include <conio.h>
#pragma comment(lib, "ws2_32")

DWORD WINAPI ThreadProc(LPVOID proc);

char chSendMsg[1024];
char chRecvMsg[1024];
bool isDisconnected = false;

SOCKET sClient;

int main()
{
	
	WSADATA wsaData;
	
	SOCKADDR_IN clientAddr;
	{
		clientAddr.sin_family = AF_INET;
		clientAddr.sin_port = htons(56789);
		InetPton(AF_INET, TEXT("222.98.247.233"), &clientAddr.sin_addr);
	}
	
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	std::cout << "연결 기다리는 중." << std::endl;
	connect(sClient, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
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


DWORD WINAPI ThreadProc(LPVOID proc)
{
	while (recv(sClient, chRecvMsg, 1024, 0) != -1)
	{
		printf("누군가: %s\r\n", chRecvMsg);
	}
	isDisconnected = true;
	return 0;
}