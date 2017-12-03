#pragma once
#include "Iterator.h"

TEST(iterator, Number)
{
	Number one(1);
	Iterator<Term*> *iterator = one.createIterator();
	iterator->first();
	ASSERT_TRUE(iterator->isDone());
}