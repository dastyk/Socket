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

	char msg[500];


	sock.SendFile("ShaderClass.h");

	cin >> msg;

	sock.ShutDown();

	sock.Destroy();

	

	return 0;
}
