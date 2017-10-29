#include "Variable.h"

Variable::Variable(string symbol) :_symbol(symbol)
{
}

Variable::~Variable()
{
}

string Variable::symbol()
{
	return _symbol;
}

string Variable::value()
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
