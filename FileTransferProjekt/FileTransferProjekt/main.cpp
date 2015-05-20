#include "UDPFileTransferClass.h"


#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	int iResult;
	
	UDPFileTransferClass ft;

	iResult = ft.Init(27015, "127.0.0.1", 27016);

	iResult = ft.SendFile("film.mp4");

	cin >> iResult;

	return 0;
}