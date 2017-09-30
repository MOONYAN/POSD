#include "Atom.h"

Atom::Atom(string symbol)
{
	_symbol = symbol;
}

Atom::~Atom()
{
}

string Atom::symbol()
{
	return _symbol;
}

string Atom::value()
{
	return _symbol;
}

bool Atom::match(Term * other)
{
	bool result = false;
	if (this == other)
	{
		result = true;
	}
	else if (other->assignable())
	{
		result = other->match(this);
	}
	return result;
}

bool Atom::assignable()
{
	return false;
}
