#pragma once
#include "Term.h"
#include <string>

class Number : public Term
{
private:
	string _symbol;
public:
	Number(int number);
	~Number();

	// Inherited via Term
	virtual string symbol() override;
	virtual string value() override;
	virtual bool match(Term& other) override;
	virtual bool tryAssign(Term& other) override;
};

