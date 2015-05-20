#ifndef _TCPSOCK_H_
#define _TCPSOCK_H_

#pragma once
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#include "FileLoader.h"

#define RERROR(e) if(e != 0) e;

class TCPSock
{
public:
	TCPSock();
	~TCPSock();


	int Init();

	int CreateSock(char* listenPort);

	void Destroy();

	int Accept();

	int SendData(char* data, ULONG dataLen);

	int RecvData(char* dataBuf, ULONG dataBufLen);

	int RecvPack(Package* pack);

	int RecvSendAck(char* data, ULONG dataLen);

	int RecvFile();

private:
	SOCKET mSocket;
	SOCKET mCSocket;
};

#endif