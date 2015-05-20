#ifndef _UDPFILETRANSFTERCLASS_H_
#define _UDPFILETRANSFTERCLASS_H_
#pragma once

#include "UDPSock.h"
#include "UDPSockListener.h"
#include "FileLoader.h"

class UDPFileTransferClass
{
public:
	UDPFileTransferClass();
	~UDPFileTransferClass();

	int Init(UINT destPort, char* destAdress, UINT listenPort);

	int RecvPack(Package* pack);

	int RecvSendAck(char* data, ULONG dataLen);

	int RecvFile();

private:
	UDPSock* mSendSock;
	UDPSockListener* mRecvSock;
	int mSq;
};

#endif