#include <string>
#include <stdint.h>

#include "file_part.h"
#include "splitter.h"

void FilePart::setName(std::string& name)
{
	this->name = name;
}

FilePart::FilePart(std::string name, uint8_t nr, std::string &data):
	nr(nr), data(data), name(name)
{}

Sentence * FilePart::getFirstSentence()const
{
	return sentences.front();
}
Sentence * FilePart::getLastSentence()const
{
	return sentences.back();
}

std::string FilePart::getName()const
{
	return name;
}
uint8_t FilePart::getNumber()const
{
	return nr;
}
void FilePart::eraseNotUsedChars()
{
	Splitter s(data);
	s.erase();
}
void FilePart::extractSentences()
{
	Splitter s(data);
	std::list<std::string> senten;
	s.splitBy("!.?", senten, false);
	for (std::string& sent : senten)
	{
		Sentence * sentence = new Sentence(sent);
		sentence->extractWords();
		sentence->sort();
		sentence->insertComas();
		this->sentences.push_back(sentence);
	}
}

std::string FilePart::extractDataHelper(Sentence* sentence)
{
	std::string data;
	if (sentence->getWords().size() > 0)
	{
		std::list<std::string>::iterator iter = sentence->getWords().begin();
		data += *iter++;
		for (; iter != sentence->getWords().end();)
			data += ' ' + *iter++;
	}
	if (sentence->hasEndOfSentence())
		data += sentence->getEndOfSentence();
	return data;
}

std::string FilePart::extractData()
{
	data.clear();
	std::list<Sentence*>::iterator it = sentences.begin();
	data += extractDataHelper(*it++);
	for (; it != sentences.end(); it++)
	{
		if ((*it)->getWords().size() > 0)
			data += " ";
		data += extractDataHelper(*it);
	}
	return data;
}

FilePart::~FilePart()
{
	for (Sentence * sentence : sentences)
	{
		delete sentence;	
	}
}
