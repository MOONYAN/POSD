#include "Leaf.h"


Leaf::Leaf(string tokenType, string tokenValue) :_tokenType(tokenType), _tokenValue(tokenValue)
{
}

Leaf::~Leaf()
{
}

string Leaf::getTokenType()
{
	return _tokenType;
}

string Leaf::getTokenValue()
{
	return _tokenValue;
}
