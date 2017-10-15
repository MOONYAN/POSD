#pragma once
#include "Term.h"
#include "Proxy.h"
class Variable : public Term
{
private:
	string _symbol;
	Term* _proxyTerm = this;
	bool canAssign();
	Proxy* _proxy = NULL;
public:
	Variable(string symbol);
	~Variable();
	bool match(Variable& other);
	bool assignable();
	Proxy* proxy();
	void setProxy(Proxy* node);
	Term* proxyTerm();

	// Inherited via Term
	virtual string symbol() override;
	virtual string value() override;
	virtual bool match(Term& other) override;
	virtual bool tryAssign(Term& other) override;
};

