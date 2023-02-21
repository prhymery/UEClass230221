#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKADDR_IN ServerSockAddr;
	ZeroMemory(&ServerSockAddr, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;
	ServerSockAddr.sin_port = htons(4000);
	//ServerSockAddr.sin_port = htons(5001);
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	
	const char* Message = "Take My Money";
	//const char* Message = "give me message.";
	int SendByte = send(ServerSocket, Message, strlen(Message) + 1, 0);
	if (SendByte == 0)
	{
		cout << "connect close." << GetLastError() << endl;
		return -1;
	}
	else if (SendByte < 0)
	{
		cout << "error close." << GetLastError() << endl;
		return -1;
	}

	//char Buffer[1024] = { 0, };
	//recv(ServerSocket, Buffer, sizeof(Buffer) - 1, 0);

	//cout << Buffer << endl;

	WSACleanup();

	return 0;
}