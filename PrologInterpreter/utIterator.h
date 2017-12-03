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

TEST(iterator, List) {
	Variable X("X");
	Variable Y("Y");
	vector<Term*> v = { &X,&Y };
	List list(v);
	Iterator<Term*> *iterator = list.createIterator();
	iterator->first();
	ASSERT_FALSE(iterator->isDone());
	ASSERT_EQ("X",iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_FALSE(iterator->isDone());
	ASSERT_EQ("Y", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}

TEST(iterator, Struct) {
	Variable X("X");
	Variable Y("Y");
	vector<Term*> v = { &X,&Y };
	Struct s(Atom("tom"),v);
	Iterator<Term*> *iterator = s.createIterator();
	iterator->first();
	ASSERT_FALSE(iterator->isDone());
	ASSERT_EQ("X", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_FALSE(iterator->isDone());
	ASSERT_EQ("Y", iterator->currentItem()->symbol());
	iterator->next();
	ASSERT_TRUE(iterator->isDone());
}