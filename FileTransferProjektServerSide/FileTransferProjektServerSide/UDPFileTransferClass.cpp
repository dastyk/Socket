#include "UDPFileTransferClass.h"


UDPFileTransferClass::UDPFileTransferClass()
{
	mSendSock = nullptr;
	mRecvSock = nullptr;
}


UDPFileTransferClass::~UDPFileTransferClass()
{
	if (mSendSock)
	{
		mSendSock->Destroy();
		delete mSendSock;
		mSendSock = nullptr;
	}
	if (mRecvSock)
	{
		mRecvSock->Destroy();
		delete mRecvSock;
		mRecvSock = nullptr;
	}
}

int UDPFileTransferClass::Init(UINT destPort, char* destAdress, UINT listenPort)
{
	int iResult;
	iResult = UDPSock::Init();
	RERROR(iResult);

	mSendSock = new UDPSock();
	iResult = mSendSock->CreateSock(destPort, destAdress);
	RERROR(iResult);

	mRecvSock = new UDPSockListener();
	iResult = mRecvSock->CreateSock();
	RERROR(iResult);

	iResult = mRecvSock->Bind(listenPort);
	RERROR(iResult);

	return 0;
}


int UDPFileTransferClass::RecvFile()
{
	Package pack;
	int iResult;
	mSq = 0;

	mRecvSock->NoTimeout();

	// Recieve and create file
	iResult = RecvPack(&pack);
	RERROR(iResult);


	FileLoader::CloseFile(&pack);

	return 0;
}

int UDPFileTransferClass::RecvPack(Package* pack)
{
	int iResult;
	char buf[500];


	// Recv file name, and send ack.
	iResult = RecvSendAck(buf, 500);
	RERROR(iResult);
	mSq++;
	pack->name = buf;

	// Recv Num of segments, and send ack.
	iResult = RecvSendAck((char*)&pack->NumPack, sizeof(pack->NumPack));
	RERROR(iResult);
	mSq++;

	FileLoader::CreateFileP(pack);
	pack->size = new unsigned int[pack->NumPack];
	for (unsigned int i = 0; i < pack->NumPack; i++)
	{
		// Recv package data size, and send ack.
		iResult = RecvSendAck((char*)&pack->size[i], sizeof(pack->size[i]));
		RERROR(iResult);
		mSq++;
		

		// Recv package data, and send ack.
		char* data = new char[pack->size[i]];
		iResult = RecvSendAck((char*)data, pack->size[i]);
		RERROR(iResult);
		mSq++;

		FileLoader::SaveDataToFile(pack, data, i);

		delete[]data;
	}
	return 0;
}

int UDPFileTransferClass::RecvSendAck(char* data, ULONG dataLen)
{
	char buf[MAXFILESIZE + sizeof(int)];
	int s = -1;
	bool ack = true;
	int iResult;
	while (s != mSq)
	{
		iResult = mRecvSock->StartListen(buf, MAXFILESIZE + sizeof(int));
		RERROR(iResult);
		memcpy(&s, buf, sizeof(int));

		iResult = mSendSock->SendData((char*)&ack, sizeof(bool));
		RERROR(iResult);


	}

	memcpy(data, buf + sizeof(int), dataLen);

	return 0;
}