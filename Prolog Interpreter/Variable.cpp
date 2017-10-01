#include "Variable.h"

bool Variable::canAssign()
{
	return _proxyTerm == NULL;
}

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
	if (canAssign())
	{
		_proxyTerm = other;
	}
	else
	{
		result = this->value() == other->value();
	}
	return result;
}

bool Variable::tryAssign(Term * other)
{
	bool result = (canAssign());
	if (result)
	{
		_proxyTerm = other;
	}
	return result;
}
