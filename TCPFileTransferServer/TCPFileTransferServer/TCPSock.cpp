#include "TCPSock.h"


TCPSock::TCPSock()
{
}


TCPSock::~TCPSock()
{
}

int TCPSock::Init()
{
	WSADATA wsaData;

	int iResult;
	// Initialize Winsock
	iResult = WSAStartup(0x101, &wsaData);
	if (iResult != 0) {
		WSACleanup();
		return WSAGetLastError();
	}

	return 0;
}

int TCPSock::CreateSock(char* listenPort)
{


	struct addrinfo *result = NULL, *ptr = NULL, hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	int iResult = getaddrinfo(NULL, listenPort,  &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 2;
	}

	mSocket = INVALID_SOCKET;

	mSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (mSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 3;
	}

	// Setup the TCP listening socket
	iResult = bind(mSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(mSocket);
		WSACleanup();
		return 4;
	}

	freeaddrinfo(result);

	if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("Listen failed with error: %ld\n", WSAGetLastError());
		closesocket(mSocket);
		WSACleanup();
		return 5;
	}
	return 0;

}


int TCPSock::Accept()
{

	mCSocket = INVALID_SOCKET;

	// Accept a client socket
	mCSocket = accept(mSocket, NULL, NULL);
	if (mCSocket == INVALID_SOCKET) {
		printf("accept failed: %d\n", WSAGetLastError());
		closesocket(mSocket);
		WSACleanup();
		return 1;
	}

	return 0;
}

int TCPSock::RecvData(char* dataBuf, ULONG dataBufLen)
{
	int iResult = recv(mCSocket, dataBuf, dataBufLen, 0);

	return iResult;
}

int TCPSock::RecvPack(Package* pack)
{
	int iResult;
	char buf[500];

	// Recv file name, and send ack.
	iResult = RecvSendAck(buf, 500);
	RERROR(iResult);
	pack->name = buf;

	// Recv package data size, and send ack.
	iResult = RecvSendAck((char*)&pack->size, sizeof(pack->size));
	RERROR(iResult);

	// Recv package data, and send ack.
	pack->data = new char[pack->size];
	iResult = RecvSendAck((char*)pack->data, pack->size);
	RERROR(iResult);

	return 0;
}

int TCPSock::RecvSendAck(char* data, ULONG dataLen)
{
	bool ack = true;
	int iResult;

	iResult = RecvData(data, dataLen);
	RERROR(iResult);
	iResult = SendData((char*)&ack, sizeof(bool));
	RERROR(iResult);

	return 0;
}


int TCPSock::SendData(char* data, ULONG dataLen)
{
	// Send data
	int iResult = send(mCSocket, data, dataLen, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		return iResult;
	}
	return 0;
}

int TCPSock::RecvFile()
{
	FileLoader f;
	Package pack;
	int iResult;

	// Recieve file
	iResult = RecvPack(&pack);
	RERROR(iResult);

	// Create file
	iResult = f.CreateFileFromPackage(&pack);
	RERROR(iResult);

	return 0;
}

void TCPSock::Destroy()
{
	closesocket(mCSocket);
	closesocket(mSocket);
	WSACleanup();
}