#include "Variable.h"

Variable::Variable(string symbol)
{
	_symbol = symbol;
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
	return _proxyTerm->value();
}

bool Variable::match(Term * other)
{
	bool result = true;
	assignable() ? _proxyTerm = other : result = false;
	return result;
}

bool Variable::assignable()
{
	return _proxyTerm == NULL;
}
