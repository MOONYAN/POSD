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
	bool match(List & other);
	int getChildCount();

	// Inherited via Term
	virtual string symbol() const override;
	virtual string value() const override;
	virtual bool match(Term & other) override;
	virtual bool tryAssign(Term & other) override;
	virtual Iterator<Term*>* createIterator() override;
};