#include "List.h"
#include "ListIterator.h"
#include "DFSIterator.h"
#include "BFSIterator.h"

Term * List::head() const
{
	if (_elements.empty())
		throw string("Accessing head in an empty list");
	return _elements[0];
}

List * List::tail() const
{
	if (_elements.empty())
		throw string("Accessing tail in an empty list");
	vector<Term *> args(_elements.begin() + 1, _elements.end());
	List* subList = new List(args);
	return subList;
}

bool List::match(List & other)
{
	int childCount = this->getChildCount();
	if (childCount != other.getChildCount())
	{
		return false;
	}
	else
	{
		for (int i = 0; i < childCount; i++)
		{
			bool result = _elements[i]->match(*other._elements[i]);
			if (!_elements[i]->match(*other._elements[i]))
			{
				return false;
			}
		}
	}
	return true;
}

int List::getChildCount()
{
	return _elements.size();
}

int List::arity()
{
	return _elements.size();
}

Term * List::args(int index)
{
	return _elements[index];
}

string List::symbol() const
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

string List::value() const
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
	bool result = other.tryAssign(*this);
	result = (this->value() == other.value());
	return result;
}

bool List::tryAssign(Term & other)
{
	return false;
}

Iterator<Term*>* List::createIterator()
{
	return new ListIterator(this);
}

Iterator<Term*>* List::createDFSIterator()
{
	return new DFSIterator(this);
}

Iterator<Term*>* List::createBFSIterator()
{
	return new BFSIterator(this);
}
