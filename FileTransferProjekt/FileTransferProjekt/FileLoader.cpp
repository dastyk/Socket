#include "FileLoader.h"


FileLoader::FileLoader()
{
}


FileLoader::~FileLoader()
{
}

int FileLoader::LoadFileData(char** data, unsigned int part, Package* package)
{

	(*data) = new char[package->size[part]];
	fread((*data), sizeof(char), package->size[part], package->file);

	return 0;
}

int FileLoader::LoadFileInfo(char* path, Package* package)
{
	unsigned int fSize;
	package->name = path;
	int error = fopen_s(&package->file, path, "rb");
	if (error != 0)
	{
		return -1;
	}
	fseek(package->file, 0, SEEK_END);
	fSize = ftell(package->file);
	rewind(package->file);
	package->NumPack = fSize / (MAXFILESIZE) + 1;
	package->size = new unsigned int[package->NumPack];
	for (unsigned int i = 0; i < package->NumPack - 1; i++)
	{
		package->size[i] = MAXFILESIZE;
		fSize -= MAXFILESIZE;
	}
	package->size[package->NumPack - 1] = fSize;

	return 0;
}

void FileLoader::CloseFile(Package* pack)
{
	fclose(pack->file);
}