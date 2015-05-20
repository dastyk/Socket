#ifndef _FILELOADER_H_
#define _FILELOADER_H_

#pragma once

#include <fstream>

#define NAMESIZE 500
#define MAXFILESIZE 51200
#include <string>


struct Package
{
	FILE* file;
	unsigned int* size;
	std::string name;
	unsigned int NumPack;
	~Package()
	{
		if (size)
			delete[] size;
	}
};

class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	static int LoadFileData(char** data, unsigned int part, Package* package);
	static int LoadFileInfo(char* path, Package* package);

	static void CloseFile(Package* pack);
private:

};

#endif