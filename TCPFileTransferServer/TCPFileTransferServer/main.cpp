#include "TCPSock.h"
#include <iostream>
using namespace std;

int main()
{
	TCPSock sock;

	cout << sock.Init() << endl;
	cout << sock.CreateSock("27015") << endl;

	cout << sock.Accept() << endl;

	char buf[500];

//	cout << "Bytes recived: " << sock.recvData(buf, 500) << endl;
	
	Package pack;

	cout << sock.recvPack(&pack);
	
	FileLoader f;

	f.CreateFileFromPackage(&pack);
	cout << buf << endl;


	cin >> buf;

	sock.Destroy();


	return 0;
}