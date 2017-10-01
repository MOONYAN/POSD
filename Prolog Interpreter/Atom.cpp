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
	bool result = other->tryAssign(this);
	result = (this->value() == other->value());
	return result;
}

bool Atom::tryAssign(Term * other)
{
	return false;
}
