#include "Number.h"

Number::Number(int number)
{
	_symbol = std::to_string(number);
}

Number::~Number()
{
}

string Number::symbol()
{
	return _symbol;
}

string Number::value()
{
	return _symbol;
}

bool Number::match(Term& other)
{	
	bool result = false;
	if (this == &other)
	{
		result = true;
	}
	else
	{
		result = other.tryAssign(*this);
	}
	return result;
}

bool Number::tryAssign(Term& other)
{
	return false;
}
