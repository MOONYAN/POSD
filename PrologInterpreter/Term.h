#pragma once
#include <iostream>
#include "Iterator.h"
using namespace std;

class Term {
public:
	virtual string symbol() const = 0;
	virtual string value() const = 0;
	virtual bool match(Term& other) = 0;
	virtual bool tryAssign(Term& other) = 0;
	virtual Iterator<Term*>* createIterator() = 0;
};