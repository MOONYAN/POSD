#pragma once
#include "Term.h"
class Var : public Term
{
private:
		string _symbol;
		Term* _proxyTerm = NULL;
		bool canAssign();
public:
	Var(string symbol);
	~Var();

	// Inherited via Term
	virtual string symbol() override;
	virtual string value() override;
	virtual bool match(Term * other) override;
	virtual bool tryAssign(Term * other) override;
};

