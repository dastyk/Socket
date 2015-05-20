
#ifndef _UDPSOCK_H_
#define _UDPSOCK_H_
#pragma once
#include <winsock2.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")

#define RERROR(e) if(e != 0) e;

class UDPSock
{
public:
	UDPSock();
	~UDPSock();

	static int Init();
	int CreateSock(UINT destPort, char* destAdress);

	void Destroy();

	int SendData(char* data, ULONG dataLen);

private:
	SOCKET mSocket;
	struct sockaddr_in sockAddr;
};

#endif