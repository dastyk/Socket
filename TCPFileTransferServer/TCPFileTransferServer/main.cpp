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

	sock.RecvFile();

	cin >> buf;

	sock.Destroy();


	return 0;
}