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
	BoolExp trueExp(true);
	BoolExp falseExp(false);
	ASSERT_FALSE(DisjExp(&falseExp, &falseExp).evaluate());
	ASSERT_TRUE(DisjExp(&trueExp, &falseExp).evaluate());
	ASSERT_TRUE(DisjExp(&falseExp, &trueExp).evaluate());
	ASSERT_TRUE(DisjExp(&trueExp, &trueExp).evaluate());
}

TEST(Exp, TestConjExp)
{
	BoolExp trueExp(true);
	BoolExp falseExp(false);
	ASSERT_FALSE(ConjExp(&falseExp, &falseExp).evaluate());
	ASSERT_FALSE(ConjExp(&trueExp, &falseExp).evaluate());
	ASSERT_FALSE(ConjExp(&falseExp, &trueExp).evaluate());
	ASSERT_TRUE(ConjExp(&trueExp, &trueExp).evaluate());
}

TEST(Exp, matchExp) {
	Atom tom("tom");
	Variable X("X");
	MatchExp mExp(&tom, &X);
	ASSERT_TRUE(mExp.evaluate());
	ASSERT_EQ("tom", X.value());
}

TEST(Exp, buildExp) {
	Scanner s("tom=X.");
	Parser p(s);
	p.buildExpression();
	ASSERT_TRUE(p.getExpressionTree());
	ASSERT_TRUE(p.getExpressionTree()->evaluate());
}

TEST(Exp, buildConjunctionExp) {
	Scanner s("Y = 2, Z = 3.");
	Parser p(s);
	p.buildExpression();
	ASSERT_TRUE(p.getExpressionTree());
	ASSERT_TRUE(p.getExpressionTree()->evaluate());
}

TEST(Exp, buildConjunctionExpFail) {
	Scanner s("Y = 2, 1 = 3.");
	Parser p(s);
	p.buildExpression();
	ASSERT_TRUE(p.getExpressionTree());
	ASSERT_FALSE(p.getExpressionTree()->evaluate());
}

TEST(Exp, buildDisjunctionExp) {
	Scanner s("X = 1; Y = 2, 1 = 3.");
	Parser p(s);
	p.buildExpression();
	ASSERT_TRUE(p.getExpressionTree());
	ASSERT_TRUE(p.getExpressionTree()->evaluate());
}

TEST(Exp, buildDisjunctionExpFail) {
	Scanner s("2 = 1; Y = 2, 1 = 3.");
	Parser p(s);
	p.buildExpression();
	ASSERT_TRUE(p.getExpressionTree());
	ASSERT_FALSE(p.getExpressionTree()->evaluate());
}

TEST(Exp, buildDisjunctionExpSuc) {
	Scanner s("2 = 1; Y = 2, Z = 3.");
	Parser p(s);
	p.buildExpression();
	ASSERT_TRUE(p.getExpressionTree());
	ASSERT_TRUE(p.getExpressionTree()->evaluate());
}