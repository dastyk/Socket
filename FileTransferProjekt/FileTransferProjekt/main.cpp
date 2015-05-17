#include "UDPSock.h"
#include <iostream>

using namespace std;

int main()
{
	int r;

	UDPSock sock;
	cout << sock.Init();

	char* msg = { "hello there.\n" };


	cout << sock.SendPackage(27015, "127.0.0.1", msg, strlen(msg) + 1);

	sock.Destroy();

	cin >> r;

	return 0;
}