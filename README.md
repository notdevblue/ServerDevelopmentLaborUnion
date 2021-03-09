# 서버개발 노동조합
![동아리 로고](https://cdn.discordapp.com/attachments/788559063759192091/818415291146305546/sirnosirno.png)<br>
곧 생길 전공동아리 깃<br>
이 동아리가 합격해서 쭉 이어 갈수도 있으니 열심히 리드미를 작성합니다.

## 좀 당황스럽습니다. 뭘 해야 하나요.
* [동신대학교 소프트웨어 커뮤니티 유튜브 강의](https://www.youtube.com/playlist?list=PLrrTotxaO6kgEMm9YYRX-jwHAHhqSt8Ke)<br><br>
우앱이가 공부하고 있는 강의 플레이리스트에요.<br>
*일단은 이거와 비슷하게 공부할것*

## 언어
* C/C++
* 어쩌면 C#<br>

## 예시 코드
* 서버
```cpp
#include <WS2tcpip.h>
#include <stdio.h>
#include <conio.h>

#pragma comment(lib, "ws2_32")

#define PORT 5678
#define PACKET_SIZE 1024

int main()
{
#pragma region 변수들
	WSADATA		wsaData;
	SOCKET		sListening;
	SOCKET		sClient;
	SOCKADDR_IN clientData;
	SOCKADDR_IN serverData;
	{
		serverData.sin_addr.s_addr	= htonl(INADDR_ANY);
		serverData.sin_port			= htons(PORT);
		serverData.sin_family		= AF_INET;
	}
	INT			clientDataSize		= sizeof(clientData);
	CHAR		chMsg[PACKET_SIZE] = "와 서노 아시는구나\r\n";
#pragma endregion


	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bind(sListening,  (SOCKADDR*)&serverData, sizeof(serverData));
	listen(sListening, SOMAXCONN);
	
	sClient = accept(sListening, (SOCKADDR*)&clientData, &clientDataSize);
	closesocket(sListening);

	send(sClient, chMsg, PACKET_SIZE, 0);

	recv(sClient, chMsg, PACKET_SIZE, 0);
	printf("%s\r\n", chMsg);


	closesocket(sClient);
	WSACleanup();
	_getch();

	return(0);
}
```
* 클라이언트
```cpp
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
```

매우 간단한 서버와 클라이언트에요.<br>
클라이언트가 접속하면 서버에서 메세지를 보내고, 클라이언트도 서버에 메세지를 보내요.
대충 이러한 코드들 + a 를 가지고 공부하는 동아리에요.<br>

## 난이도
* 매우 어려워요.
* 아주 어려워요.
* 많이 어려워요.
* 진짜 어려워요.<br>

## 뭐 배워요?
저 위에 있는 강의 링크에 있는것들 배워요.<br>
글구 된다면 다른 동아리 침략해서 서버를 심어주고 옵시다.<br><br>

## 서버개발 노동조합 팀원
* 팀장 한우엽
* 권혁준
* 김경혁
* 김형주
* 명재문
* 손환주
* 유원석<br><br>
* *Groovy*
