#pragma once
#include "Iterator.h"
#include "Number.h"
#include "Atom.h"
#include "Variable.h"
#include "List.h"
#include "Struct.h"

TEST(iterator, Number)
{
	Number one(1);
	Iterator<Term*> *iterator = one.createIterator();
	iterator->first();
	ASSERT_TRUE(iterator->isDone());
}

TEST(iterator, Atom)
{
	Atom tom("tom");
	Iterator<Term*> *iterator = tom.createIterator();
	iterator->first();
	ASSERT_TRUE(iterator->isDone());
}

TEST(iterator, Variable)
{
	Variable X("X");
	Iterator<Term*> *iterator = X.createIterator();
	iterator->first();
	ASSERT_TRUE(iterator->isDone());
}

