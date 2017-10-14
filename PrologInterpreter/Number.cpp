#include "Number.h"

Number::Number(int number)
{
	_symbol = std::to_string(number);
}

Number::Number(double number)
{
	stringstream ss;
	ss << number;
	ss >> _symbol;
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
	bool result = other.tryAssign(*this);
	result = (this->value() == other.value());
	return result;
}

bool Number::tryAssign(Term& other)
{
	return false;
}
