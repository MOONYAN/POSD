#pragma once
#include "Iterator.h"

template<class T>
class NullIterator : public Iterator<T>
{
public:
	NullIterator(){}
	~NullIterator(){}

	// Inherited via Iterator
	virtual void first() override
	{
	}

	virtual void next() override
	{
	}

	virtual T currentItem() const override
	{
		return nullptr;
	}

	virtual bool isDone() const override
	{
		return true;
	}
};