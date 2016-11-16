
#include <fstream>
#include "file_reader.h"
#include "splitter.h"

FileReader::FileReader(const char * filename):
	filename(filename)
{
	file.open(filename, std::ios_base::in);
	if (!file.is_open())
	{
		throw "Cannot open file: " + this->filename;
	}
}

uint8_t FileReader::getPartNumber()
{
	Splitter s(filename);
	std::list<std::string> list;
	s.splitBy(".", list, true);
	if (list.size() == 1)
	{
		return 0;
	}
	else if (list.size() == 2)
	{
		filename = list.front();
		return std::atoi(list.back().c_str());
	}
	else
	{
		throw "ERROR: Cant retrieve part number of file: " + filename;
	}
}

FilePart *FileReader::getFilePart()
{
	if (!file.is_open())
	{
		throw "Cannot open file: " + this->filename;
	}
	std::string s(std::istreambuf_iterator<char>(file), {});
	return new FilePart(filename, this->getPartNumber(), s);
}

FileReader::~FileReader()
{
	if (file.is_open())
	{
		file.close();
	}
}
