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
	else
	{
		result = other->tryAssign(this);
	}
	return result;
}

bool Atom::assignable()
{
	return false;
}

bool Atom::tryAssign(Term * other)
{
	return false;
}
