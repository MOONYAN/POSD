#include "List.h"

Term * List::head() const
{
	return _elements[0];
}

List * List::tail() const
{
	vector<Term *> args(_elements.begin() + 1, _elements.end());
	List* subList = new List(args);
	return subList;
}

string List::symbol()
{
	stringstream ss;
	ss << "[";
	for (int i = 0, maxpos = _elements.size() - 1; i <= maxpos; i++)
	{
		ss << _elements[i]->symbol();
		if (i != maxpos)
			ss << ", ";
	}
	ss << "]";
	return ss.str();
}

string List::value()
{
	stringstream ss;
	ss << "[";
	for (int i = 0, maxpos = _elements.size() - 1; i <= maxpos; i++)
	{
		ss << _elements[i]->value();
		if (i != maxpos)
			ss << ", ";
	}
	ss << "]";
	return ss.str();
}

bool List::match(Term & other)
{
	return false;
}

bool List::tryAssign(Term & other)
{
	return false;
}
