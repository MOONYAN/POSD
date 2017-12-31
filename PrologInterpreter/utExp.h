#pragma once
#include "Exp.h"
#include "Term.h"
#include "Atom.h"
#include "Variable.h"

TEST(Exp, TestBoolExp)
{
	ASSERT_TRUE(BoolExp(true).evaluate());
	ASSERT_FALSE(BoolExp(false).evaluate());
}

TEST(Exp, TestDisjExp)
{
	ASSERT_FALSE(DisjExp(&BoolExp(false), &BoolExp(false)).evaluate());
	ASSERT_TRUE(DisjExp(&BoolExp(true), &BoolExp(false)).evaluate());
	ASSERT_TRUE(DisjExp(&BoolExp(false), &BoolExp(true)).evaluate());
	ASSERT_TRUE(DisjExp(&BoolExp(true), &BoolExp(true)).evaluate());
}

TEST(Exp, TestConjExp)
{
	ASSERT_FALSE(ConjExp(&BoolExp(false), &BoolExp(false)).evaluate());
	ASSERT_FALSE(ConjExp(&BoolExp(true), &BoolExp(false)).evaluate());
	ASSERT_FALSE(ConjExp(&BoolExp(false), &BoolExp(true)).evaluate());
	ASSERT_TRUE(ConjExp(&BoolExp(true), &BoolExp(true)).evaluate());
}

TEST(Exp, matchExp) {
	Atom tom("tom");
	Variable X("X");
	MatchExp mExp(&tom, &X);
	ASSERT_TRUE(mExp.evaluate());
	ASSERT_EQ("tom", X.value());
}