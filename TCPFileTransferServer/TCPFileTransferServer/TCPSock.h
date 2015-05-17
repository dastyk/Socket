#ifndef _TCPSOCK_H_
#define _TCPSOCK_H_

#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include "FileLoader.h"

class TCPSock
{
public:
	TCPSock();
	~TCPSock();


	int Init();

	int CreateSock(char* listenPort);

	void Destroy();

	int Accept();

	int recvData(char* dataBuf, ULONG dataBufLen);

	int recvPack(Package* pack);



private:
	SOCKET mSocket;
	SOCKET mCSocket;
};

#endif