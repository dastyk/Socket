#pragma once
#ifndef _UDPSOCKLISTENER_H_
#define _UDPSOCKLISTENER_H_

#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <iostream>

using namespace std;
class UDPSockListener
{
public:
	UDPSockListener();
	~UDPSockListener();

	int Init();
	int CreateSock();

	void Destroy();

	int Bind(UINT listenPort);

	int StartListen(char* dataBuf, UINT dataBufLen);

private:
	SOCKET mSocket;
};

#endif