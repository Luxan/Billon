#pragma once

class Comma
{
	size_t pos;
public:
	size_t getPos();
	Comma(size_t pos);
	Comma(Comma &comma);
	~Comma();
};

