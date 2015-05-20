#include "UDPSockListener.h"


UDPSockListener::UDPSockListener()
{
}


UDPSockListener::~UDPSockListener()
{
}

int UDPSockListener::Init()
{
	WSADATA wsaData;

	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		WSACleanup();
		return iResult;
	}


	return 0;
}

int UDPSockListener::CreateSock()
{

	// Create the socket.
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mSocket == INVALID_SOCKET)
	{
		return WSAGetLastError();
	}

	return 0;
}


void UDPSockListener::Timeout()
{

	timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	// Set Timeout for recv call
	setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&tv), sizeof(timeval));
}

void UDPSockListener::NoTimeout()
{
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	// Set Timeout for recv call
	setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&tv), sizeof(timeval));
}

int UDPSockListener::Bind(UINT listenPort)
{
	int iResult;

	struct sockaddr_in listener;
	listener.sin_family = AF_INET;
	listener.sin_port = listenPort;
	listener.sin_addr.s_addr = INADDR_ANY;


	// Bind the socket.
	iResult = bind(mSocket, (struct sockaddr*)&listener, sizeof(listener));
	if (iResult == SOCKET_ERROR)
	{
		return -1;
	}

	return 0;
}

int UDPSockListener::StartListen(char* dataBuf, UINT dataBufLen)
{
	struct sockaddr_in sourceAddr;
	int sLen = sizeof(sourceAddr);

	int iResult;

	iResult = recvfrom(mSocket, dataBuf, dataBufLen, 0, (struct sockaddr*)&sourceAddr, &sLen);

	return 0;
}

void UDPSockListener::Destroy()
{
	closesocket(mSocket);
	WSACleanup();
}