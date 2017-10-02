#pragma once
#include <iostream>
using namespace std;

class Term {
public:
	virtual string symbol() = 0;
	virtual string value() = 0;
	virtual bool match(Term* other) = 0;
	virtual bool tryAssign(Term* other) = 0;
};