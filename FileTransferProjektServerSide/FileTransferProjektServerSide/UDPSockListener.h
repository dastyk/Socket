#pragma once
#ifndef _UDPSOCKLISTENER_H_
#define _UDPSOCKLISTENER_H_

#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")

class UDPSockListener
{
public:
	UDPSockListener();
	~UDPSockListener();

	int Init();
	void Destroy();

	int Bind(UINT listenPort);

	int StartListen(char* dataBuf, UINT dataBufLen);

private:
	SOCKET mSocket;
};

#endif