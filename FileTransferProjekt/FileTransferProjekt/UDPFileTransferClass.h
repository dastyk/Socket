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

	int SendPackage(Package* pack);

	int SendWaitForAck(char* data, ULONG dataLen);

	int SendFile(char* path);
private:
	UDPSock* mSendSock;
	UDPSockListener* mRecvSock;
	int mSq;
};

#endif