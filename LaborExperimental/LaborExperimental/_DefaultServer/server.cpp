#include <WS2tcpip.h>
#include <cstdio>

#pragma comment(lib, "ws2_32")

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET sListening;
	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN serverData;
	{
		serverData.sin_addr.s_addr = INADDR_ANY;
		serverData.sin_port = htons(56789);
		serverData.sin_family = AF_INET;
	}

	bind(sListening, (SOCKADDR*)&serverData, sizeof(serverData));

	listen(sListening, SOMAXCONN);
	printf("리스닝...\r\n");
	SOCKADDR_IN clientData;
	INT clientDataSize = sizeof(clientData);

	SOCKET sClient = accept(sListening, (SOCKADDR*)&clientData, &clientDataSize);
	closesocket(sListening);
	printf("클라이언트 접속함.\r\n");
	CHAR buffer[1024];
	INT bufferSize = 1024;
	INT leftBufferSize = bufferSize;
	INT lBuffer = 0;
	INT index = 0;

	while (leftBufferSize > 0)
	{
		lBuffer = send(sClient, &buffer[index], leftBufferSize, 0);
		leftBufferSize -= lBuffer;
		index += lBuffer;
	}

	closesocket(sClient);
	WSACleanup();
	
	system("pause");

	return(0);
}