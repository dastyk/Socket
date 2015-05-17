#include "UDPSockListener.h"

#include <iostream>

using namespace std;

#define BUFLEN (200*1024)

int main()
{
	int r;
	UDPSockListener sock;
	sock.Init();

	char buf[BUFLEN];

	cout << sock.Bind(27015);


	cout << sock.StartListen(buf, BUFLEN) << endl;
	cout << buf;

	sock.Destroy();

	cin >> r;


	return 0;
}