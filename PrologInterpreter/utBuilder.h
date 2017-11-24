#pragma once
#include "Builder.h"
#include <vector>

using namespace std;

TEST(BuilderTest, AtomInstance)
{
	Builder builder;
	Atom* term = builder.getAtomInstance("tom");
	ASSERT_EQ("tom", term->symbol());
	Atom* again = builder.getAtomInstance("tom");
	ASSERT_EQ("tom", again->symbol());
	ASSERT_EQ(term, again);
}

TEST(BuilderTest, NumberInstance)
{
	Builder builder;
	Number* term = builder.getNumberInstance("1");
	ASSERT_EQ("1", term->symbol());
	Number* again = builder.getNumberInstance("1");
	ASSERT_EQ("1", again->symbol());
	ASSERT_EQ(term, again);
}

TEST(BuilderTest, VariableInstance)
{
	Builder builder;
	Atom* tom = builder.getAtomInstance("tom");
	Variable* term = builder.getVariableInstance("X");
	term->match(*tom);
	ASSERT_EQ("X", term->symbol());
	ASSERT_EQ("tom", term->value());
	Variable* again = builder.getVariableInstance("X");
	ASSERT_EQ("X", again->symbol());
	ASSERT_EQ("tom", again->value());
	ASSERT_EQ(term, again);
}

TEST(BuilderTest, StructInstance)
{
	Builder builder;
	Atom* tom = builder.getAtomInstance("tom");	
	vector<Term *> terms = { tom };
	Struct* term = builder.getStructInstance(*tom, terms);
	//term->match(*tom);
	ASSERT_EQ("tom(tom)", term->symbol());
	Struct* again = builder.getStructInstance(*tom, terms);
	ASSERT_EQ(term, again);
}

TEST(BuilderTest, ListInstance)
{
	Builder builder;
	Atom* tom = builder.getAtomInstance("tom");
	vector<Term *> terms = { tom };
	List* term = builder.getListInstance(terms);
	//term->match(*tom);
	ASSERT_EQ("[tom]", term->symbol());
	List* again = builder.getListInstance(terms);
	ASSERT_EQ(term, again);
}