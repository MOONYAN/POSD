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
	Struct(Atom name, vector<Term*>& childs);
	~Struct();
	Atom name();
	Term* args(int index);

	// Inherited via Term
	virtual string symbol() override;
	virtual string value() override;
	virtual bool match(Term & other) override;
	virtual bool tryAssign(Term & other) override;
};

