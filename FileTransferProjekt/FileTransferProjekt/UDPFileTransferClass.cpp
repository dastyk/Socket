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

	cout << "Setting up the file transfer protocol..." << endl;

	int iResult;
	iResult = UDPSock::Init();
	if (iResult != 0) return iResult;


	mSendSock = new UDPSock();
	iResult = mSendSock->CreateSock(destPort, destAdress);
	if (iResult != 0) return iResult;

	mRecvSock = new UDPSockListener();
	iResult = mRecvSock->CreateSock();
	if (iResult != 0) return iResult;

	iResult = mRecvSock->Bind(listenPort);
	if (iResult != 0) return iResult;

	cout << "File transfer protocol setup finished." << endl << endl;

	return 0;
}


int UDPFileTransferClass::SendPackage(Package* pack)
{
	int iResult;

	// Send file name, and wait for ack.
	iResult = SendWaitForAck((char*)pack->name.c_str(), pack->name.size() + 1);
	if (iResult != 0) return iResult;
	mSq++;

	// Send Num of segments.
	iResult = SendWaitForAck((char*)(&pack->NumPack), sizeof(pack->NumPack));
	if (iResult != 0) return iResult;
	mSq++;

	for (unsigned int i = 0; i < pack->NumPack; i++)
	{
		// Send package data size, and wait for ack.
		iResult = SendWaitForAck((char*)(&pack->size[i]), sizeof(pack->size[i]));
		if (iResult != 0) return iResult;
		mSq++;

		char* buf;

		FileLoader::LoadFileData(&buf, i, pack);

		// Send package data, and wait for ack.
		iResult = SendWaitForAck(buf, pack->size[i]);
		if (iResult != 0) return iResult;
		mSq++;

		delete[] buf;
	}
	

	return 0;
}

int UDPFileTransferClass::SendWaitForAck(char* data, ULONG dataLen)
{
	char buf[MAXFILESIZE + sizeof(int)];
	memcpy(buf, &mSq, sizeof(int));
	memcpy(buf + sizeof(int), data, dataLen);
	bool ack = false;
	int iResult;
	while (!ack)
	{
		iResult = mSendSock->SendData(buf, sizeof(int) + dataLen);
		if (iResult != 0) return iResult;

		iResult = mRecvSock->StartListen((char*)&ack, sizeof(bool));
		if (iResult != 0) return iResult;
	}


	return 0;
}

int UDPFileTransferClass::SendFile(char* path)
{
	Package pack;
	int iResult;
	mSq = 0;
	
	cout << "Loading file: " << path << "..." << endl;

	// Load file
	iResult = FileLoader::LoadFileInfo(path, &pack);
	if (iResult != 0) return iResult;

	cout << "Sending file: " << path << "..." << endl;
	// Send file
	iResult = SendPackage(&pack);
	if (iResult != 0) return iResult;

	cout << "File has been sent." << endl << endl;


	FileLoader::CloseFile(&pack);

	return 0;
}