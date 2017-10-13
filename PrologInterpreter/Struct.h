#pragma once
#include "Term.h"
#include "Atom.h"
#include <vector>
#include <sstream>

class Struct : public Term
{
private:
	Atom* _name;
	vector<Term*> _childs;
public:
	Struct(string name, vector<Term*>& childs);
	~Struct();
	string name();
	Term* args(int index);

	// Inherited via Term
	virtual string symbol() override;
	virtual string value() override;
	virtual bool match(Term & other) override;
	virtual bool tryAssign(Term & other) override;
};

