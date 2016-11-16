#include <vector>
#include "splitter.h"


Splitter::Splitter(std::string &data):
	data(data)
{}

void Splitter::erase()
{
	std::string::iterator iter = data.begin();
	while (iter != data.end())
	{
		char c = *iter;
		if (!((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) ||
			c == 32 || c == 33 ||  c == 44 || c == 46 || c == 63))
		{
			iter = data.erase(iter);
			continue;
		}
		iter++;
	}
}

void Splitter::splitBy(std::string delimiter, std::list<std::string>& list, bool eraseDelimiter)
{
	size_t pos = data.length();
	if (pos == 0)
		return;
	size_t currentPos;
	char currentDelimiter;
	std::string token;
	size_t offset = 0;
	int found = 0;
	while (offset < data.length())
	{
		for (std::string::iterator iter = delimiter.begin(); iter != delimiter.end(); iter++)
		{
			if ((currentPos = data.find(*iter, offset)) != std::string::npos)
			{
				found++;
				if (currentPos < pos)
				{
					pos = currentPos;
					currentDelimiter = *iter;
				}
			}
		}
		if (!found)
		{
			if (eraseDelimiter)
			{
				token = data.substr(offset, data.length() - offset);
			}
			else
			{
				token = data.substr(offset, data.length() - offset);
			}
			offset = data.length();
			list.push_back(token);
		}
		else
		{
			if (eraseDelimiter)
			{
				if (offset == pos)
				{
					offset++;
					pos = data.length();
					found = 0;
					continue;
				}
				token = data.substr(offset, pos - offset);
			}
			else
			{
				token = data.substr(offset, pos + 1 - offset);
			}
			offset = pos + 1;
			list.push_back(token);
			pos = data.length();
		}
		found = 0;
	}
}

Splitter::~Splitter()
{}
