using System;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace LaborUnionCSharpWSA
{
    class Program
    {
        static void Main(string[] args)
        {
            Socket sClient = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            var clientAddr = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 56789);
            sClient.Connect(clientAddr);


            string cmd = string.Empty;
            byte[] sendBuffer = Encoding.UTF8.GetBytes(cmd);
            byte[] recvBuffer = new byte[1024];
            int recvSize = 0;

            sClient.Send(sendBuffer, SocketFlags.None);

            recvSize = sClient.Receive(recvBuffer);

            string data = Encoding.UTF8.GetString(recvBuffer, 0, recvSize);
            Console.WriteLine(data);

            sClient.Close();
        }
    }
}
