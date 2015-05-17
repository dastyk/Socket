#include "FileLoader.h"


FileLoader::FileLoader()
{
}


FileLoader::~FileLoader()
{
}

int FileLoader::LoadFile(char* path, Package* package)
{
	FILE* file;
	package->name = path;
	int error = fopen_s(&file, path, "rb");
	if (error != 0)
	{
		return -1;
	}
	fseek(file, 0, SEEK_END);
	package->size = ftell(file);
	rewind(file);

	package->data = new char[package->size];
	fread(package->data, sizeof(char), package->size, file);

	return 0;
}
