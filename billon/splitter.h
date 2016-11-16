#pragma once
#include <string>
#include <list>

class Splitter
{
	std::string &data;
public:
	Splitter(std::string &data);
	void erase();
	void splitBy(std::string d, std::list<std::string>& list, bool eraseDelimiter);
	~Splitter();
};

