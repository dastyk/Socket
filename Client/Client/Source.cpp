#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#define DEFAULT_PORT 27015
#define DEFAULT_BUFLEN 512

#include <winsock2.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main(int argc, char *argv[]) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	WSADATA wsaData;
	int iResult;



	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		WSACleanup();
		cin >> iResult;
		return 1;
	}


	SOCKET s;

	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s== INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		cin >> iResult;
		return 1;
	}


	struct sockaddr_in server;

	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons(DEFAULT_PORT);


	iResult = connect(s, (sockaddr*)&server, sizeof(server));
	if (iResult == SOCKET_ERROR)
	{
		closesocket(s);
		s = INVALID_SOCKET;
	}

	if (s == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		cin >> iResult;
		return 3;
	}

	int recvbuflen = DEFAULT_BUFLEN;

	char sendbuf[DEFAULT_BUFLEN];
	char recvbuf[DEFAULT_BUFLEN];

	do
	{
		cout << "Enter message:" << endl;

		cin >> sendbuf;

		// Send an initial buffer
		iResult = send(s, sendbuf, (int)strlen(sendbuf)+1, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(s);
			WSACleanup();
			return 1;
		}

		printf("Bytes Sent: %ld\n", iResult);


	} while (strcmp(sendbuf, "exit"));


	// shutdown the connection for sending since no more data will be sent
	// the client can still use the ConnectSocket for receiving data
	iResult = shutdown(s, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed: %d\n", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return 1;
	}
	WSACleanup();

	return 0;
}
