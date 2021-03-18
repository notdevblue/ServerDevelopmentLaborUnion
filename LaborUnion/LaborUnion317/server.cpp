#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32")

int main()
{
	// WSA == (WebSocketAPI, WinSockAPI, WebServiceAPI...)
	WSAData wsaData;
	
	// 여기서 wsaData에 변수를 넣어 줘요.
	// 함수가 알아서 해주는 좋은 새상
	WSAStartup(MAKEWORD(2, 2), &wsaData); // 나중에 배울 클래스의 생성자와 비슷하다고 보면 돼요.
	
	// MAKEWORD == 함수에 들어가는 값이 WORD(short) 형식이라서 소수점을 보낼 수 없어요.
	//			   MAKEWORD(x, y) 는 x.y 로 만들어서 보내줘요.
	//			   뭔가 자새히 설명하려니 어렵

	SOCKET serverSocket; // 소켓 구조체 변수
	SOCKADDR_IN serverAddr; // 소켓 정보 구조체 변수
	{ // 가독성 위해서 중괄호 사용했어요.
		serverAddr.sin_family = AF_INET; // #define 을 사용해서 숫자를 문자로 바꿔둔 거에요. (좀더 기억하기 쉽게) (마우스 올려 보면 알 수 있음)
		// AF_INET  은 192.168.0.2			와 같이 숫자.숫자.숫자.숫자 로 된 주소를 의미해요.
		// AF_INET6 는 2001:0DB8::1428:57ab 와 같이 요상한 16진수로 된 주소를 의매해요.

		serverAddr.sin_port = htons(5678); // 포트 번호는 상관은 없지만 short 안에서 표현이 가능한 수로 해야 해요. + http/s 통신 등의 사용되는 포트는 사용할 수 없어요.
		// 12345678 을 메모리에 저장하는 방법
		// 인터넷 표준 12 34 56 78
		// 컴퓨터 표준 78 56 34 12
		// 저장 방법이 달라서 서로 변환해야 해요.
		// htons == Host To Network Short (Host 와 Network 위치를 바꾸면 Network 에서 Host 로 변환이 가능해요)

		InetPton(AF_INET, TEXT("127.0.0.1"), &serverAddr.sin_addr);
		// TEXT("주소") 로 쓴 이유는 char 는 1바이트 단위로 문자를 저장하지만,
		// InetPton 함수는 2바이트 단위로 저장하는 wchar_t 를 요구해서 변환이 필요했어요.
		// 숫자.숫자.숫자.숫자 로 이루어진 문자열을 숫자로 변환하여 serverAddr.sin_addr 에 넣어주는 함수에요.
	}
	
	serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	// SOCK_STREAM = TCP/IP 를 사용한다는 의미라고 일단 설명할게요.
	// IPPROTO_TCP = TCP 통신 프로토콜을 사용한다는 의미에요.

	bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)); // 소켓 구조체 변수와 우리가 작성한 소켓 정보를 묶어 주는 역할을 합니다.
	// (SOCKADDR*)&serverAddr == 다음 시간에 설명할게요.
	
	WSACleanup(); // 나중에 배울 클래스의 소멸자와 비슷하다고 보면 됩니다.
	return 0;
}