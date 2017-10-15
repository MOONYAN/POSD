#pragma once
#include "Proxy.h"
#include "Variable.h"

TEST(Proxy, constructor) {
	Proxy proxy("proxy");
	ASSERT_EQ("proxy", proxy.value());
}

TEST(Proxy, Var_match_Var)
{
	Variable X("X");
	Variable Y("Y");
	ASSERT_TRUE(X.match(Y));
	EXPECT_EQ("Y", X.value());
	EXPECT_EQ("Y", Y.value());
	EXPECT_EQ("Y", X.proxy()->value());
	EXPECT_EQ("Y", Y.proxy()->value());
}