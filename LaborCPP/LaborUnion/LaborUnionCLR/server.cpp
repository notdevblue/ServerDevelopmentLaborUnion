#using <System.dll>

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;

int main()
{
	Socket^ socket = gcnew Socket(AddressFamily::InterNetwork,SocketType::Stream,ProtocolType::Tcp);


	return 0;
}