#pragma once
#include "Term.h"
#include "Atom.h"
#include <vector>
#include <sstream>

class Struct : public Term
{
private:
	Atom _name;
	vector<Term*> _childs;
public:
	Struct(Atom name, vector<Term*> childs);
	~Struct();
	Atom& name();
	Term* args(int index);
	bool match(Struct & other);
	int arity();

	// Inherited via Term
	virtual string symbol() const override;
	virtual string value() const override;
	virtual bool match(Term & other) override;
	virtual bool tryAssign(Term & other) override;
	virtual Iterator<Term*>* createIterator() override;
	virtual Iterator<Term*>* createDFSIterator() override;
	virtual Iterator<Term*>* createBFSIterator() override;
};

