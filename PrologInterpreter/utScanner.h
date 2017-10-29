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
