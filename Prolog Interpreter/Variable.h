#pragma once
#include "Term.h"
class Variable : public Term
{
private:
		string _symbol;
		Term* _proxyTerm = NULL;
		bool canAssign();
public:
	Variable(string symbol);
	~Variable();

	// Inherited via Term
	virtual string symbol() override;
	virtual string value() override;
	virtual bool match(Term * other) override;
	virtual bool tryAssign(Term * other) override;
};

