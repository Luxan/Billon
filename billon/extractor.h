#pragma once
#include <map>
#include "file_part.h"

class Extractor
{
	std::map<uint8_t, FilePart *> parts;
	void sortTwoSentences(Sentence * lastSentence, Sentence * firstSentence);
	void changeDestinationName(FilePart * part);
public:
	Extractor();
	void extractAndSortParts();
	void putFilePart(FilePart * filepart);

	std::list<FilePart *> getFileParts();

	~Extractor();
};

