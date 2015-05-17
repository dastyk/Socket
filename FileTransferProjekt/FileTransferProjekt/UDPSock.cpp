#include "UDPSock.h"


UDPSock::UDPSock()
{
}


UDPSock::~UDPSock()
{
}

int UDPSock::Init()
{
	WSADATA wsaData;

	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		WSACleanup();
		return -1;
	}

	// Create the socket.
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return -2;
	}

	return 0;
}


int UDPSock::SendPackage(UINT destPort, char* destAdress, char* sendData, ULONG len)
{
	struct sockaddr_in sockAddr;
	int iResult = 0;

	memset((char*)&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = destPort;
	sockAddr.sin_addr.S_un.S_addr = inet_addr(destAdress);

	iResult = sendto(mSocket, sendData, len, 0, (struct  sockaddr*)&sockAddr, sizeof(sockAddr));
	if (iResult == SOCKET_ERROR) {
		return -1;
	}

	return 0;
}

void UDPSock::Destroy()
{
	closesocket(mSocket);
	WSACleanup();
}