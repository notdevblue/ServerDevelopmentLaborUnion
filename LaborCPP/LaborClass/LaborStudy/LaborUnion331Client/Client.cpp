#include <WS2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "ws2_32")

int main()
{
	SOCKET sClient;
	SOCKADDR_IN clientAddr;

	WSADATA wsaData;

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(56789);
	InetPton(AF_INET, TEXT("127.0.0.1"), &clientAddr.sin_addr.s_addr);

	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	connect(sClient, (SOCKADDR*)&clientAddr, sizeof(clientAddr));

	char chMsg[1024];
	recv(sClient, chMsg, 1024, 0);

	printf("%s", chMsg);

	closesocket(sClient);
	WSACleanup();





	return(0);
}
