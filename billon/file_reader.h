#pragma once
#include <string>
#include <fstream>
#include <list>

#include "sentence.h"
#include "file_part.h"

class FileReader
{
private:
	std::string filename;
	std::ifstream file;
	std::list<Sentence> sentences;
	uint8_t getPartNumber();
public:
	FileReader(const char * filename);
	FilePart *getFilePart();
	~FileReader();
};

