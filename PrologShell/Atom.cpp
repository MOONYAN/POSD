#include "Atom.h"

Atom::Atom(string symbol)
{
	_symbol = symbol;
}

Atom::~Atom()
{
}

string Atom::symbol() const
{
	return _symbol;
}

string Atom::value() const
{
	return _symbol;
}

bool Atom::match(Term& other)
{
	bool result = other.tryAssign(*this);
	result = (this->value() == other.value());
	return result;
}

bool Atom::tryAssign(Term& other)
{
	return false;
}

Iterator<Term*>* Atom::createIterator()
{
	return new NullIterator<Term*>();
}

Iterator<Term*>* Atom::createDFSIterator()
{
	return new NullIterator<Term*>();
}

Iterator<Term*>* Atom::createBFSIterator()
{
	return new NullIterator<Term*>();
}
