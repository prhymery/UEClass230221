#include <iostream>
#include <WinSock2.h>	// 윈도우에서 제공하는 소켓?

#pragma comment(lib, "ws2_32.lib")	// library

using namespace std;

int main()
{
	WSAData wsaData;

	// WinSock 초기화
	int Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != 0)
	{
		cout << "Winsock2 Error" << endl;
		return -1;
	}

	SOCKET ServerSocket = socket(PF_INET, SOCK_STREAM, 0);	// 소켓 생성
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "can't make socket." << GetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = AF_INET;	// IPv4
	ServerSockAddr.sin_port = htons(4000);	// 서버 4000번
	//ServerSockAddr.sin_port = htons(5001);	// 서버 4000번
	ServerSockAddr.sin_addr.s_addr = INADDR_ANY; // 랜카드 여러개일 경우 아무거나 사용

	Result = bind(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));
	if (Result == SOCKET_ERROR)
	{
		cout << "can't bind." << GetLastError() << endl;
		return -1;
	}

	Result = listen(ServerSocket, 0);
	if (Result == SOCKET_ERROR)
	{
		cout << "can't listen." << GetLastError() << endl;
		return -1;
	}

	SOCKADDR_IN ClientSockAddr;
	memset(&ClientSockAddr, 0, sizeof(ClientSockAddr));
	int ClientSockAddrLength = sizeof(ClientSockAddr);
	int ClientSocket = accept(ServerSocket, (SOCKADDR*)&ClientSockAddr, &ClientSockAddrLength);
	if (ClientSocket == INVALID_SOCKET)
	{
		cout << "can't accept." << GetLastError() << endl;
		return -1;
	}

	char Buffer[1024] = { 0, };
	recv(ClientSocket, Buffer, sizeof(Buffer) - 1, 0);

	cout << Buffer << endl;

	//const char* Message = "show me the money.";
	//int SendByte = send(ServerSocket, Message, strlen(Message) + 1, 0);
	/*int SendByte = send(ClientSocket, Message, strlen(Message) + 1, 0);
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

	char Buffer[1024] = { 0, };
	recv(ClientSocket, Buffer, sizeof(Buffer) - 1, 0);

	cout << 1 << endl;
	cout << Buffer << endl;*/

	closesocket(ClientSocket);
	closesocket(ServerSocket);

	// WinSock 정리
	WSACleanup();


	return 0;
}