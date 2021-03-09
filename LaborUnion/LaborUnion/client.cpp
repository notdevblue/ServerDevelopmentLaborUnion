#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>
#pragma comment(lib, "ws2_32")

#define PORT 5678
#define PACKET_SIZE 1024

int main()
{
#pragma region 변수들
	WSADATA wsaData;
	SOCKET sClient;
	SOCKADDR_IN clientData;
	{
		InetPton(AF_INET, TEXT("127.0.0.1"), &clientData.sin_addr.s_addr);
		clientData.sin_port = htons(PORT);
		clientData.sin_family = AF_INET;
	}
	CHAR chMsg[PACKET_SIZE];
#pragma endregion

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(sClient, (SOCKADDR*)&clientData, sizeof(clientData));

	recv(sClient, chMsg, PACKET_SIZE, 0);
	printf("%s", chMsg);
	
	strcpy_s(chMsg, PACKET_SIZE, "와 서버개발 노동조합 아시는구나\r\n");
	send(sClient, chMsg, PACKET_SIZE, 0);


	closesocket(sClient);
	WSACleanup();
	_getch();

	return(0);
}