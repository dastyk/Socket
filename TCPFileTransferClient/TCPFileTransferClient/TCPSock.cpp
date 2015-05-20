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
		return -1;
	}
	return 0;
}

int TCPSock::CreateSock()
{

	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (mSocket == INVALID_SOCKET)
	{
		printf("Could not create socket : %d \n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	return 0;
}

int TCPSock::Connect(UINT destPort, char* destAdress)
{

	struct sockaddr_in server;

	server.sin_addr.s_addr = inet_addr(destAdress);
	server.sin_family = AF_INET;
	server.sin_port = htons(destPort);


	int iResult = connect(mSocket, (sockaddr*)&server, sizeof(server));
	if (iResult == SOCKET_ERROR)
	{
		closesocket(mSocket);
		mSocket = INVALID_SOCKET;
	}

	if (mSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 3;
	}
	return 0;
}

int TCPSock::SendData(char* data, ULONG dataLen)
{
	// Send data
	int iResult = send(mSocket, data, dataLen, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		return iResult;
	}
	return 0;
}

int TCPSock::SendPackage(Package* pack)
{
	int iResult;

	// Send file name, and wait for ack.
	iResult = SendWaitForAck((char*)pack->name.c_str(), pack->name.size() + 1);
	RERROR(iResult);

	// Send package data size, and wait for ack.
	iResult = SendWaitForAck((char*)(&pack->size), sizeof(pack->size));
	RERROR(iResult);

	// Send package data, and wait for ack.
	iResult = SendWaitForAck(pack->data, pack->size);
	RERROR(iResult);

	return 0;
}


int TCPSock::RecvData(char* dataBuf, ULONG dataBufLen)
{
	int iResult = recv(mSocket, dataBuf, dataBufLen, 0);
	if (iResult == SOCKET_ERROR) {
		printf("Recv failed: %d\n", WSAGetLastError());
		return iResult;
	}

	return 0;
}

int TCPSock::SendWaitForAck(char* data, ULONG dataLen)
{
	bool ack = false;
	int iResult;
	while (!ack)
	{
		iResult = SendData(data, dataLen);
		RERROR(iResult);

		iResult = RecvData((char*)&ack, sizeof(bool));
		RERROR(iResult);
	}

	return 0;
}

int TCPSock::SendFile(char* path)
{
	FileLoader f;
	Package pack;
	int iResult;

	// Load file
	iResult = f.LoadFile(path, &pack);
	RERROR(iResult);

	// Send file
	iResult = SendPackage(&pack);
	RERROR(iResult);

	return 0;
}

int TCPSock::ShutDown()
{
	// shutdown the connection for sending since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	int iResult = shutdown(mSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(mSocket);
		WSACleanup();
		return 1;
	}

	return 0;
}


void TCPSock::Destroy()
{
	closesocket(mSocket);
	WSACleanup();
}