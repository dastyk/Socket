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

	cout << "Initializing Winsock..." << endl;

	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) 
	{
		cout << "Winsock could not initialize, Error: " << iResult << "." << endl << endl;
		WSACleanup();
		return iResult;
	}
	cout << "Winsock Initialized." << endl << endl;
	

	return 0;
}


int UDPSock::CreateSock(UINT destPort, char* destAdress)
{
	cout << "Creating UDP Sendsocket on DestPort: " << destPort << " DestAdress: " << destAdress << "..." << endl;

	// Create the socket.
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mSocket == INVALID_SOCKET)
	{
		cout << "UDP Sendsocket could not be created, Error: " << WSAGetLastError() << "." << endl << endl;

		WSACleanup();
		return WSAGetLastError();
	}

	memset((char*)&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = destPort;
	sockAddr.sin_addr.S_un.S_addr = inet_addr(destAdress);

	cout << "UDP Sendsocket created on DestPort: " << destPort << " DestAdress: " << destAdress << "." << endl << endl;

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