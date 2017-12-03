#pragma once
#include "Term.h"
#include "NullIterator.h"

class Variable : public Term
{
private:
	string _symbol;
	Term* _instance = NULL;
public:
	Variable(string symbol);
	~Variable();
	// Inherited via Term
	virtual string symbol() const override;
	virtual string value() const override;
	virtual bool match(Term& other) override;
	virtual bool tryAssign(Term& other) override;
	virtual Iterator<Term*>* createIterator() override;
};

