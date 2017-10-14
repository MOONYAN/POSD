#include "Variable.h"

bool Variable::canAssign()
{
	return _proxyTerm == this;
}

Variable::Variable(string symbol)
{
	_symbol = symbol;
}

Variable::~Variable()
{
}

Proxy * Variable::proxy()
{
	return _proxy;
}

string Variable::symbol()
{
	return _symbol;
}

string Variable::value()
{
	string result = this->_symbol;
	if (!canAssign())
	{
		result = _proxyTerm->value();
	}
	return result;
}

bool Variable::match(Term& other)
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

bool Variable::tryAssign(Term& other)
{
	bool result = (canAssign());
	if (result)
	{
		_proxyTerm = &other;
	}
	return result;
}
