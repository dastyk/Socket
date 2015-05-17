
#ifndef _UDPSOCK_H_
#define _UDPSOCK_H_
#pragma once
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
class UDPSock
{
public:
	UDPSock();
	~UDPSock();

	int Init();
	void Destroy();

	int SendPackage(UINT destPort, char* destAdress, char* sendData, ULONG len);



private:
	SOCKET mSocket;
};

#endif