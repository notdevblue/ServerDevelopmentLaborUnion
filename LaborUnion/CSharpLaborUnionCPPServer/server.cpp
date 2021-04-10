#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#pragma comment(lib, "ws2_32")

int main()
{
	WSADATA		wsaData;
	SOCKET		sListening;
	SOCKET		sClient;
	SOCKADDR_IN serverAddr;
	{
		serverAddr.sin_addr.s_addr = INADDR_ANY;
		serverAddr.sin_port = htons(56789);
		serverAddr.sin_family = AF_INET;
	}
	SOCKADDR_IN clientAddr;
	INT clientSize = sizeof(clientAddr);
	INT posX = 0;
	CHAR buffer[1024];

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	bind(sListening, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	listen(sListening, SOMAXCONN);
	sClient = accept(sListening, (SOCKADDR*)&clientAddr, &clientSize);
	closesocket(sListening);
	
	recv(sClient, buffer, 1024, 0);
	sscanf_s(buffer, "%d", &posX);
	
	



	while (true)
	{
		strcpy_s(buffer, 1024, std::to_string(posX).c_str());

		send(sClient, buffer, 1024, 0);	

	}
	
	


	closesocket(sClient);
	WSACleanup();

	_getch();
	return(0);
}