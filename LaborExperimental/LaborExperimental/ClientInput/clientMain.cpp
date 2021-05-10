#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>
#pragma comment(lib, "ws2_32")


int main()
{
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
	while ((input[0] = tolower(input[0] = _getch())) != 'q')
	{
		send(clientSocket, input, 1, 0);
	}


	closesocket(clientSocket);

	WSACleanup();
	
	return(0);
}