#pragma once
#include "Scanner.h"

TEST(Scanner, Var)
{
	auto doAssert = [](string inputVar) {
		Scanner scanner(inputVar);
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ("Variable", leaf->getTokenType());
		ASSERT_EQ(inputVar, leaf->getTokenValue());
	};
	doAssert("X");
	doAssert("Xyz");
	doAssert("_xyZ");
	doAssert("_XyZ");
	doAssert("_123_");
	doAssert("__1ab");
	doAssert("__");
}

TEST(Scanner, Atom)
{
	auto doAssert = [](string inputAtom) {
		Scanner scanner(inputAtom);
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ("Atom", leaf->getTokenType());
		ASSERT_EQ(inputAtom, leaf->getTokenValue());
	};
	doAssert("xX");
	doAssert("xXyz");
	doAssert("x_xyZ");
	doAssert("x_XyZ");
	doAssert("x_123_");
	doAssert("x__1ab");
	doAssert("x__");
}

TEST(Scanner, Number)
{
	auto doAssert = [](string inputNumber, string expectNumber) {
		Scanner scanner(inputNumber);
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ("Number", leaf->getTokenType());
		ASSERT_EQ(expectNumber, leaf->getTokenValue());
	};
	doAssert("0", "0");
	doAssert("0.1", "0.1");
	doAssert("123.4567", "123.4567");
	//doAssert("-0", "0");
	//doAssert("-0.1", "-0.1");
	//doAssert("-123.4567", "-123.4567");
	//doAssert("+0", "0");
	//doAssert("+0.1", "0.1");
	//doAssert("+123.4567", "123.4567");
	//doAssert("0123", "123");
	//doAssert("0010", "10");
	//doAssert("0.1000", "0.1");
}

TEST(Scanner, keywords)
{
	auto doAssert = [](string inputstring, string expectType) {
		Scanner scanner(inputstring);
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(inputstring, leaf->getTokenValue());
	};
	doAssert(",", "Comma");
	doAssert("=", "Match");
	doAssert("[", "ListBegin");
	doAssert("]", "ListEnd");
	doAssert("(", "StructBegin");
	doAssert(")", "StructEnd");
	doAssert("", "EndOfString");
}

//X=Y
TEST(Scanner, VarMatchVar)
{
	Scanner scanner("X=Y");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("X", "Variable");
	doAssert("=", "Match");
	doAssert("Y", "Variable");
}

//X=tom
TEST(Scanner, VarMatchAtom)
{
	Scanner scanner("X=tom");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("X", "Variable");
	doAssert("=", "Match");
	doAssert("tom", "Atom");
}

//X=123.4567
TEST(Scanner, VarMatchNumber)
{
	Scanner scanner("X=123.4567");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("X", "Variable");
	doAssert("=", "Match");
	doAssert("123.4567", "Number");
}

//tom=123.4567
TEST(Scanner, AtomMatchNumber)
{
	Scanner scanner("tom=123.4567");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("tom", "Atom");
	doAssert("=", "Match");
	doAssert("123.4567", "Number");
}

//123.4567=X
TEST(Scanner, NumberMatchVar)
{
	Scanner scanner("123.4567=X");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("123.4567", "Number");
	doAssert("=", "Match");
	doAssert("X", "Variable");
}

//X=s(tom)
TEST(Scanner, VarMatchStructWithAtom)
{
	Scanner scanner("X=s(tom)");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("X", "Variable");
	doAssert("=", "Match");
	doAssert("s", "Atom");
	doAssert("(", "StructBegin");
	doAssert("tom", "Atom");
	doAssert(")", "StructEnd");
}

//X=s(123.4567)
TEST(Scanner, VarMatchStructWithNumber)
{
	Scanner scanner("X=s(123.4567)");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("X", "Variable");
	doAssert("=", "Match");
	doAssert("s", "Atom");
	doAssert("(", "StructBegin");
	doAssert("123.4567", "Number");
	doAssert(")", "StructEnd");
}

//X=s(_abc)
TEST(Scanner, VarMatchStructWithVar)
{
	Scanner scanner("X=s(_abc)");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("X", "Variable");
	doAssert("=", "Match");
	doAssert("s", "Atom");
	doAssert("(", "StructBegin");
	doAssert("_abc", "Variable");
	doAssert(")", "StructEnd");
}

//X=[_abc]
TEST(Scanner, VarMatchListWithVar)
{
	Scanner scanner("X=[_abc]");
	auto doAssert = [&](string expectValue, string expectType) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectType, leaf->getTokenType());
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	doAssert("X", "Variable");
	doAssert("=", "Match");
	doAssert("[", "ListBegin");
	doAssert("_abc", "Variable");
	doAssert("]", "ListEnd");
}

//X=s(father(tom,sam),mother(merry,leo))
TEST(Scanner, VarMatchNestedStruct)
{
	Scanner scanner("X=s(father(tom,sam),mother(merry,leo))");
	auto doAssert = [&](string expectValue) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	auto result = { "X","=","s","(","father","(","tom",",","sam",")",",","mother","(","merry",",","leo",")",")" };
	for each (auto value in result)
	{
		doAssert(value);
	}
}

//X=[father(tom,sam),mother(merry,leo)]
TEST(Scanner, VarMatchListWithStruct)
{
	Scanner scanner("X=[father(tom,sam),mother(merry,leo)]");
	auto doAssert = [&](string expectValue) {
		Leaf* leaf = scanner.getNextLeaf();
		ASSERT_EQ(expectValue, leaf->getTokenValue());
	};
	auto result = { "X","=","[","father","(","tom",",","sam",")",",","mother","(","merry",",","leo",")","]" };
	for each (auto value in result)
	{
		doAssert(value);
	}
}