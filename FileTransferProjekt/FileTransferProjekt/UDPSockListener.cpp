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

int UDPSockListener::CreateSock()
{
	cout << "Creating UDP Recvsocket..." << endl;

	// Create the socket.
	mSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (mSocket == INVALID_SOCKET)
	{
		cout << "UDP Recvsocket could not be created, Error: " << WSAGetLastError() << "." << endl << endl;

		return WSAGetLastError();
	}

	timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 0;

	// Set Timeout for recv call
	setsockopt(mSocket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&tv), sizeof(timeval));

	cout << "UDP Recvsocket created." << endl << endl;

	return 0;
}


int UDPSockListener::Bind(UINT listenPort)
{
	int iResult;

	cout << "Binding UDP Recvsocket to port: "<< listenPort << "..." << endl;

	struct sockaddr_in listener;
	listener.sin_family = AF_INET;
	listener.sin_port = listenPort;
	listener.sin_addr.s_addr = INADDR_ANY;


	// Bind the socket.
	iResult = bind(mSocket, (struct sockaddr*)&listener, sizeof(listener));
	if (iResult == SOCKET_ERROR)
	{
		cout << "UDP Recvsocket could not be bound to port: " << listenPort << ", Error: " << iResult << "." << endl << endl;

		return iResult;
	}

	cout << "UDP Recvsocket bound to port: " << listenPort << "." << endl << endl;

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