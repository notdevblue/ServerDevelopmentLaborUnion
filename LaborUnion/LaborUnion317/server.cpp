#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
	WSAData wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET serverSocket;
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(5678);
	InetPton(AF_INET, TEXT("127.0.0.1"), &serverAddr.sin_addr);
	
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	/*
	1203

	컴퓨터
	1 | 2 | 3 | 4 |
	3   0   2   1
	
	네트워크
	1 | 2 | 3 | 4 |
	1   2   0   3


	*/




	
	WSACleanup();
	return 0;
}