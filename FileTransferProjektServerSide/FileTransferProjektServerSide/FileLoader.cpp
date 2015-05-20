#include "FileLoader.h"


FileLoader::FileLoader()
{
}


FileLoader::~FileLoader()
{
}

int FileLoader::CreateFileP(Package* pack)
{
	int error = fopen_s(&pack->file, pack->name.c_str(), "wb");
	if (error != 0)
	{
		return -1;
	}
	return 0;
}

int FileLoader::SaveDataToFile(Package* pack, char* data, int p)
{
	fwrite(data, sizeof(char), pack->size[p], pack->file);
	return 0;
}

void FileLoader::CloseFile(Package* pack)
{
	fclose(pack->file);
}