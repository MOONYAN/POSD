#pragma once
#include "Leaf.h"

TEST(Leaf, construct)
{	
	auto doAssert = [](string tokenType, string tokenValue) {
		Leaf leaf(tokenType, tokenValue);
		ASSERT_EQ(tokenType, leaf.getTokenType());
		ASSERT_EQ(tokenValue, leaf.getTokenValue());
	};
	doAssert("Variable", "X");
	doAssert("Atom", "x");
	doAssert("Number", "9487");
	doAssert("Comma", ",");
	doAssert("Match", "=");
	doAssert("ListBegin", "[");
	doAssert("ListEnd", "]");
	doAssert("StructBegin", "(");
	doAssert("StructEnd", ")");
	doAssert("EndOfString", "");
}