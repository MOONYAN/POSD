#include "Struct.h"

Struct::Struct(Atom & name, vector<Term*>& childs) :_name(name), _childs(childs)
{	
}

Struct::~Struct()
{
}

Atom Struct::name()
{
	return _name;
}

Term * Struct::args(int index)
{
	return _childs[index];
}

string Struct::symbol()
{
	stringstream ss;
	ss << _name.symbol() << "(";
	for (int i = 0, maxpos = _childs.size() - 1; i <= maxpos; i++)
	{
		ss << _childs[i]->symbol();
		if (i == maxpos)
			ss << ")";
		else
			ss << ", ";
	}
	return ss.str();
}

string Struct::value()
{
	return string();
}

bool Struct::match(Term & other)
{
	return false;
}

bool Struct::tryAssign(Term & other)
{
	return false;
}