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
		clientAddr.sin_port = htons(5678);
		InetPton(AF_INET, TEXT("127.0.0.1"), &clientAddr.sin_addr);
	}
	HANDLE hThread;



	WSAStartup(MAKEWORD(2, 2), &wsaData);
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	std::cout << "연결 기다리는 중." << std::endl;
	connect(sClient, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
	std::cout << "연결 성공." << std::endl;


	hThread = CreateThread(NULL, 0, ThreadProc, NULL, 0, NULL);

	while (!isDisconnected)
	{	
		std::cin.getline(chSendMsg, 1024);
		send(sClient, chSendMsg, 1024, 0);
	}

	
	

	_getch();

	closesocket(sClient);
	WSACleanup();
	CloseHandle(hThread);
	return(0);
}


DWORD WINAPI ThreadProc(LPVOID proc)
{
	while (!isDisconnected)
	{
		isDisconnected = recv(sClient, chRecvMsg, 1024, 0) == -1;
		std::cout << "서버: " << chRecvMsg << std::endl;
	}
	return 0;
}