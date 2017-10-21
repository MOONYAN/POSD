#include "List.h"

Term * List::head() const
{
	return nullptr;
}

List * List::tail() const
{
	return nullptr;
}

string List::symbol()
{
	return string();
}

string List::value()
{
	return string();
}

bool List::match(Term & other)
{
	return false;
}

bool List::tryAssign(Term & other)
{
	return false;
}
