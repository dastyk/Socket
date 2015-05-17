#ifndef _FILELOADER_H_
#define _FILELOADER_H_

#pragma once

#include <fstream>

#define NAMESIZE 500

#include <string>


struct Package
{
	unsigned int size;
	std::string name;
	char* data;
	~Package()
	{
		if (data)delete[] data;	
	}
};

class FileLoader
{
public:
	FileLoader();
	~FileLoader();

	int LoadFile(char* path, Package* package);

};

#endif