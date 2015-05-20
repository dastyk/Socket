#ifndef _TCPSOCK_H_
#define _TCPSOCK_H_

#pragma once
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>
#include "FileLoader.h"


#define RERROR(e) if(e != 0) e;

class TCPSock
{
public:
	TCPSock();
	~TCPSock();


	int Init();
	int CreateSock();


	int Connect(UINT destPort, char* destAdress);

	void Destroy();

	int RecvData(char* dataBuf, ULONG dataBufLen);


	int SendData(char* data, ULONG dataLen);
	int SendPackage(Package* pack);

	int SendWaitForAck(char* data, ULONG dataLen);

	int SendFile(char* path);

	int ShutDown();

private:
	SOCKET mSocket;
};

#endif