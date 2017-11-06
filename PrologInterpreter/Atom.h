#pragma once
#include "Term.h"
class Atom : public Term
{
private:
	string _symbol;

public:
	Atom(string symbol);
	~Atom();

	// Inherited via Term
	virtual string symbol() const override;
	virtual string value() const override;
	virtual bool match(Term& other) override;
	virtual bool tryAssign(Term& other) override;
};

