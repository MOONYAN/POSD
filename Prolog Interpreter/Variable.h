#pragma once
#include "Term.h"
class Variable : public Term
{
private:
		string _symbol;
		Term* _proxyTerm = NULL;
public:
	Variable(string symbol);
	~Variable();

	// Inherited via Term
	virtual string symbol() override;
	virtual string value() override;
	virtual bool match(Term * other) override;
	virtual bool assignable() override;
};

