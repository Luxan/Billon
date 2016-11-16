#include "file_writer.h"


FileWriter::FileWriter(FilePart * part):
	part(part), file(part->getName())
{}

bool FileWriter::write()
{
	if (file.is_open())
	{
		file << part->extractData() << std::endl;
		return true;
	}
	return false;
}

FileWriter::~FileWriter()
{
	file.close();
}
