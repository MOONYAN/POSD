#pragma once
#include "Iterator.h"
#include "Struct.h"

class StructIterator :public Iterator<Term*>
{
public:
	StructIterator(Struct* s) :_struct(s) {}
	~StructIterator() {}

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
		return _struct->args(_index);
	}

	virtual bool isDone() const override
	{
		return _index >= _struct->arity();
	}
private:
	Struct* _struct;
	int _index = 0;
};