#include "Variable.h"

Variable::Variable(string symbol) :_symbol(symbol)
{
}

Variable::~Variable()
{
}

string Variable::symbol() const
{
	return _symbol;
}

string Variable::value() const
{
	if (_instance)
	{
		return _instance->value();
	}
	else
	{
		return symbol();
	}
}

bool Variable::match(Term& other)
{
	if (this == &other)
	{
		return true;
	}
	else if(!_instance)
	{
		_instance = &other;
		return true;
	}
	else
	{
		return _instance->match(other);
	}
}

bool Variable::tryAssign(Term& other)
{
	return this->match(other);
}

Iterator<Term*>* Variable::createIterator()
{
	return new NullIterator<Term*>();
}

Iterator<Term*>* Variable::createDFSIterator()
{
	return new NullIterator<Term*>();
}

Iterator<Term*>* Variable::createBFSIterator()
{
	return new NullIterator<Term*>();
}
