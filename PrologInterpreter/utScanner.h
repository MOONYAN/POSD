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
