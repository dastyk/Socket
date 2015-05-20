#include "UDPFileTransferClass.h"
#include <iostream>

using namespace std;

#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int r;
	
	UDPFileTransferClass ft;

	cout << ft.Init(27016, "127.0.0.1", 27015) << endl;

	cout << ft.RecvFile() << endl;

	cin >> r;


	return 0;
}