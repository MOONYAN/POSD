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

Number::Number(string number):_symbol(number)
{
}

Number::~Number()
{
}

string Number::symbol() const
{
	return _symbol;
}

string Number::value() const
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

Iterator<Term*>* Number::createIterator()
{
	return new NullIterator<Term*>();
}

Iterator<Term*>* Number::createDFSIterator()
{
	return new NullIterator<Term*>();
}
