#include "variable.h"

bool Var::canAssign()
{
	return _proxyTerm == NULL;
}

Var::Var(string symbol)
{
	_symbol = symbol;
}

Var::~Var()
{
}

string Var::symbol()
{
	return _symbol;
}

string Var::value()
{
	return _proxyTerm->value();
}

bool Var::match(Term& other)
{
	bool result = true;
	if (canAssign())
	{
		_proxyTerm = &other;
	}
	else
	{
		result = this->value() == other.value();
	}
	return result;
}

bool Var::tryAssign(Term& other)
{
	bool result = (canAssign());
	if (result)
	{
		_proxyTerm = &other;
	}
	return result;
}
