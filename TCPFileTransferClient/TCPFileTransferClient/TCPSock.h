#ifndef _TCPSOCK_H_
#define _TCPSOCK_H_

#pragma once
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include "FileLoader.h"

class TCPSock
{
public:
	TCPSock();
	~TCPSock();


	int Init();
	int CreateSock();


	int Connect(UINT destPort, char* destAdress);

	void Destroy();

	int SendPackage(Package* pack);

	int ShutDown();

private:
	SOCKET mSocket;
};

#endif