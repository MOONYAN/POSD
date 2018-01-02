#include "Builder.h"



Builder::Builder()
{
}


Builder::~Builder()
{
}

void Builder::clearPool()
{
	_termMap.clear();
}

Atom * Builder::getAtomInstance(string symbol)
{
	if (_termMap[symbol] == nullptr)
	{
		_termMap[symbol] = new Atom(symbol);
	}
	return dynamic_cast<Atom*>(_termMap[symbol]);
}

Variable * Builder::getVariableInstance(string symbol)
{
	if (_termMap[symbol] == nullptr)
	{
		_termMap[symbol] = new Variable(symbol);
	}
	return dynamic_cast<Variable*>(_termMap[symbol]);
}

Number * Builder::getNumberInstance(string symbol)
{
	if (_termMap[symbol] == nullptr)
	{
		_termMap[symbol] = new Number(symbol);
	}
	return dynamic_cast<Number*>(_termMap[symbol]);
}

Struct * Builder::getStructInstance(Atom name, vector<Term*> childs)
{
	Struct* s = new Struct(name, childs);
	string symbol = s->symbol();
	if (_termMap[symbol] == nullptr)
	{
		_termMap[symbol] = s;
	}
	return dynamic_cast<Struct*>(_termMap[symbol]);
}

List * Builder::getListInstance(vector<Term*> elements)
{
	List* s = new List(elements);
	string symbol = s->symbol();
	if (_termMap[symbol] == nullptr)
	{
		_termMap[symbol] = s;
	}
	return dynamic_cast<List*>(_termMap[symbol]);
}