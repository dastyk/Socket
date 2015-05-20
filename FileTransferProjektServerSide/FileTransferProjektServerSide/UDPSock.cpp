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
		return iResult;
	}

	

	return 0;
}


int UDPSock::CreateSock(UINT destPort, char* destAdress)
{

	// Create the socket.
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mSocket == INVALID_SOCKET)
	{
		WSACleanup();
		return WSAGetLastError();
	}

	memset((char*)&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = destPort;
	sockAddr.sin_addr.S_un.S_addr = inet_addr(destAdress);

	return 0;
}





int UDPSock::SendData(char* data, ULONG dataLen)
{
	int iResult = sendto(mSocket, data, dataLen, 0, (struct  sockaddr*)&sockAddr, sizeof(sockAddr));
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		return iResult;
	}

	return 0;
}



void UDPSock::Destroy()
{
	closesocket(mSocket);
	WSACleanup();
}