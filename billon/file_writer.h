#pragma once
#include <string>
#include <fstream>
#include <list>

#include "sentence.h"
#include "file_part.h"

class FileWriter
{
	std::ofstream file;
	FilePart * part;
public:
	FileWriter(FilePart * part);
	bool write();
	~FileWriter();
};
