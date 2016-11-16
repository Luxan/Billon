#pragma once
#include <list>
#include "comma.h"

class Sentence
{
	char endOfSentence = 0;
	std::string data;
	std::list<std::string> words;
	std::list<Comma> commas;
public:
	void insertComas();
	char getEndOfSentence()const;
	bool hasEndOfSentence()const;
	void sort(); 
	void ejectComas();
	void extractWords();
	std::list<std::string> &getWords();
	Sentence(std::string &data);
	~Sentence();
};

