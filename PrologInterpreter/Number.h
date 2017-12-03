#pragma once
#include "Term.h"
#include "NullIterator.h"
#include <string>
#include <sstream>

class Number : public Term
{
private:
	string _symbol;
public:
	Number(int number);
	Number(double number);
	Number(string number);
	~Number();

	// Inherited via Term
	virtual string symbol() const override;
	virtual string value() const override;
	virtual bool match(Term& other) override;
	virtual bool tryAssign(Term& other) override;
	virtual Iterator<Term*>* createIterator() override;
};

