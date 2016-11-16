#include "comma.h"

Comma::Comma(size_t pos) :
	pos(pos)
{}

size_t Comma::getPos()
{
	return pos;
}

Comma::Comma(Comma &comma)
{
	this->pos = comma.pos;
}

Comma::~Comma()
{}
