#pragma once
#include "Term.h"
#include <vector>
#include <sstream>

class List : public Term 
{
private:
	vector<Term *> _elements;
public:
	List() : _elements() {}
	List(vector<Term *> const & elements) :_elements(elements) {}
	Term * head() const;
	List * tail() const;

	// Inherited via Term
	virtual string symbol() override;
	virtual string value() override;
	virtual bool match(Term & other) override;
	virtual bool tryAssign(Term & other) override;
};
