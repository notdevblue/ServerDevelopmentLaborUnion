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
*예시 코드*<br>
```cpp
#include <WS2tcpip.h>
#include <stdio.h>

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
	CHAR		chMsg[PACKET_SIZE] = "Connected.\r\nServer will shut down in 5 secs.";
#pragma endregion


	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bind(sListening, (SOCKADDR*)&serverData, sizeof(serverData));
	listen(sListening, SOMAXCONN);
	
	sClient = accept(sListening, (SOCKADDR*)&clientData, &clientDataSize);
	closesocket(sListening);

	send(sClient, chMsg, PACKET_SIZE, 0);
	Sleep(5000);

	closesocket(sClient);
	
	WSACleanup();
	return(0);
}
```
매우 간단한 서버에요.<br>
클라이언트가 접속하면 메세지를 보내고 5초 후에 알아서 꺼지는 서버입니다.<br>
대충 이러한 코드들 + a 를 가지고 공부하는 동아리에요.<br>

## 난이도
* 매우 어려워요.
* 아주 어려워요.
* 많이 어려워요.
