#pragma once
#include "Exp.h"

TEST(Exp, TestBoolExp)
{
	ASSERT_TRUE(BoolExp(true).evaluate());
	ASSERT_FALSE(BoolExp(false).evaluate());
}

