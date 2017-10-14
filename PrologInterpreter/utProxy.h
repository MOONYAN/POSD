#pragma once
#include "Proxy.h"

TEST(Proxy, constructor) {
	Proxy proxy("proxy");
	ASSERT_EQ("proxy", proxy.value());
}