#include "TCPSock.h"
#include <iostream>
#include "FileLoader.h"

using namespace std;
int main()
{

	TCPSock sock;

	cout << sock.Init() << endl;
	cout << sock.CreateSock() << endl;

	cout << sock.Connect(27015, "127.0.0.1") << endl;

	char msg[] = { "Message" };


	FileLoader f;
	Package pack;
	if (f.LoadFile("file.txt", &pack) >= 0)
	{

	}

	cout << sock.SendPackage(&pack) << endl;

	cin >> msg;

	sock.ShutDown();

	sock.Destroy();

	

	return 0;
}
