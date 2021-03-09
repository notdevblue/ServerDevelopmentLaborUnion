#include <conio.h>
#include <iostream>
#include <WS2tcpip.h>
#include <sstream>
#include <ctime>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/string.hpp>

#pragma comment(lib, "ws2_32")

#define PORT 5678
#define PACKET_SIZE 1024

enum Sender
{
	Client,
	Server
};

#pragma pack(push, 1)
struct LaborUnionPacket
{
	unsigned	short		senderID;
				std::string message;
	template<typename Archive>
	void serialize(Archive& ar, const unsigned int version)
	{
		ar& senderID;
		ar& message;
	}
};
#pragma pack(pop)

int main()
{
#pragma region 변수들
	WSADATA		wsaData;
	SOCKET		sListening;
	SOCKET		sClient;
	SOCKADDR_IN clientData;
	SOCKADDR_IN serverData;
	{
		serverData.sin_addr.s_addr = htonl(INADDR_ANY);
		serverData.sin_port = htons(PORT);
		serverData.sin_family = AF_INET;
	}
	INT			clientDataSize = sizeof(clientData);
	CHAR		chMsg[PACKET_SIZE];

	LaborUnionPacket				packet;
	std::stringstream				ss;

#pragma endregion


	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sListening = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	bind(sListening, (SOCKADDR*)&serverData, sizeof(serverData));
	listen(sListening, SOMAXCONN);

	sClient = accept(sListening, (SOCKADDR*)&clientData, &clientDataSize);
	closesocket(sListening);

#pragma region 직렬화
	// 이쪽은 아직 공부중이라 정확하지 않을 수 있음.
	packet.message = "이것은 데이터 직렬화이다아아\r\n";
	packet.senderID = Server;
	boost::archive::text_oarchive oa(ss);
	oa << packet;
	send(sClient, ss.str().c_str(), PACKET_SIZE, 0);

	ss.clear();

	recv(sClient, chMsg, PACKET_SIZE, 0);
	ss << chMsg;
	boost::archive::text_iarchive ia(ss);
	ia >> packet;

	std::cout << packet.message;
	if (packet.senderID == Server)
		std::cout << "서버에서 보낸 메세지" << std::endl;
	else if (packet.senderID == Client)
		std::cout << "클라이언트에서 보낸 메세지" << std::endl;
	
#pragma endregion

	closesocket(sClient);
	WSACleanup();
	_getch();

	return(0);
}