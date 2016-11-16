#include <vector>
#include <algorithm>

#include "sentence.h"
#include "splitter.h"

static bool compare_nocase(const std::string& first, const std::string& second)
{
	unsigned int i = 0;
	while ((i<first.length()) && (i<second.length()))
	{
		if (tolower(first[i])<tolower(second[i])) return true;
		else if (tolower(first[i])>tolower(second[i])) return false;
		++i;
	}
	return (first.length() < second.length());
}

char Sentence::getEndOfSentence()const
{
	return endOfSentence;
}

bool Sentence::hasEndOfSentence()const
{
	return endOfSentence != 0;
}

void Sentence::insertComas()
{
	size_t pos = 0;
	for (std::string &str : words)
	{
		for (Comma c : commas)
		{
			if (pos == c.getPos())
				str += ',';
		}
		pos++;
	}

	commas.clear();
}

void Sentence::sort()
{
	words.sort(compare_nocase);
	words.reverse();
}

std::list<std::string> &Sentence::getWords()
{
	return words;
}

Sentence::Sentence(std::string &data):
	data(data)
{}

void Sentence::ejectComas()
{
	size_t pos = 0;
	for (std::string& w : words)
	{
		if (w.back() == ',')
		{
			commas.push_back(Comma(pos));
			w.erase(w.length() - 1);
		}
		pos++;
	}
}

void Sentence::extractWords()
{
	if (data.length() == 0)
	{
		return;
	}
	if (data.back() == '.' || data.back() == '!' || data.back() == '?')
	{
		endOfSentence = data.back();
		data.erase(data.length() - 1, 1);
	}
	Splitter s(data);
	s.splitBy(" ", words, true);
	size_t pos = 0;
	for (std::string& w : words)
	{
		if (w.back() == ',')
		{
			commas.push_back(Comma(pos));
			w.erase(w.length() - 1);
		}
		std::reverse(w.begin(), w.end());
		pos++;
	}
}

Sentence::~Sentence(){}

