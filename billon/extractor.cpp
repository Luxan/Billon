#include "extractor.h"

Extractor::Extractor(){}

void Extractor::sortTwoSentences(Sentence * lastSentence, Sentence * firstSentence)
{
	size_t sizeOflast = lastSentence->getWords().size();
	size_t sizeOfFirst = firstSentence->getWords().size();

	for (std::list<std::string>::iterator itr = firstSentence->getWords().begin();
		itr != firstSentence->getWords().end();
		itr++)
	{
		lastSentence->getWords().push_back(*itr);
	}
	firstSentence->getWords().clear();
	lastSentence->ejectComas();
	lastSentence->sort();
	lastSentence->insertComas();

	for (size_t i = 0; i < sizeOfFirst; i++)
	{
		firstSentence->getWords().push_back(lastSentence->getWords().back());
		lastSentence->getWords().pop_back();
	}
	firstSentence->getWords().reverse();
}

void Extractor::changeDestinationName(FilePart * part)
{
	if (part->getNumber() == 0)
		part->setName(part->getName() + ".wynik");
	else
		part->setName(part->getName() + "." + std::to_string(part->getNumber()) + ".wynik");
}

void Extractor::extractAndSortParts()
{
	FilePart * part;
	Sentence * lastSentence = nullptr;
	Sentence * firstSentence = nullptr;
	for (std::pair<uint8_t, FilePart *> pair : parts)
	{
		part = pair.second;
		part->eraseNotUsedChars();
		part->extractSentences();
		if (lastSentence)
		{
			firstSentence = part->getFirstSentence();
			sortTwoSentences(lastSentence, firstSentence);
			firstSentence = nullptr;
			lastSentence = nullptr;
		}
		if (!part->getLastSentence()->hasEndOfSentence())
		{
			lastSentence = part->getLastSentence();
		}

		changeDestinationName(part);
	}
}

std::list<FilePart *> Extractor::getFileParts()
{
	std::list<FilePart *> list;
	for (std::pair<uint8_t, FilePart *> pair : parts)
	{
		list.push_back(pair.second);
	}
	return list;
}

void Extractor::putFilePart(FilePart * filepart)
{
	if (parts.find(filepart->getNumber()) == parts.end())
		parts[filepart->getNumber()] = filepart;
	else
		delete filepart;
}

Extractor::~Extractor()
{
	for (std::pair<uint8_t, FilePart *> pair : parts)
		delete pair.second;
}
