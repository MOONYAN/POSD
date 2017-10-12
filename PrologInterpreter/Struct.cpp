#include "Struct.h"

Struct::Struct(string name, vector<Term*>& childs) :_childs(childs)
{
	_name = new Atom(name);
}

Struct::~Struct()
{
}

string Struct::name()
{
	return _name->symbol();
}

Term * Struct::args(int index)
{
	return _childs[index];
}

string Struct::symbol()
{
	return string();
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
