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

bool Number::match(Term * other)
{	
	return this->value() == other->value();
}
