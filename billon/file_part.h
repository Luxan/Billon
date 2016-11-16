#pragma once

#include <stdint.h>
#include <string>

#include "sentence.h"

class FilePart
{
private:
	uint8_t nr;
	std::string data;
	std::string name;
	std::list<Sentence *> sentences;
	std::string extractDataHelper(Sentence* sentence);
public:
	FilePart(std::string name, uint8_t nr, std::string& data);
	void setName(std::string &name);
	Sentence * getFirstSentence()const;
	Sentence * getLastSentence()const;
	void eraseNotUsedChars();
	void extractSentences();
	std::string extractData();
	std::string getName()const;
	uint8_t getNumber()const;
	~FilePart();
};

