#pragma once
#include "Iterator.h"
#include "List.h"

class ListIterator :public Iterator<Term*>
{
public:
	ListIterator(List* list) :_list(list) {}
	~ListIterator() {}

	// Inherited via Iterator
	virtual void first() override
	{
		_index = 0;
	}

	virtual void next() override
	{
		_index++;
	}

	virtual Term* currentItem() const override
	{
		return _list->args(_index);
	}

	virtual bool isDone() const override
	{
		return _index >= _list->arity();
	}
private:
	List* _list;
	int _index = 0;
};