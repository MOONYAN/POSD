#pragma once
#include <map>
#include <vector>
#include "Term.h"
#include "Atom.h"
#include "Variable.h"
#include "Number.h"
#include "Struct.h"
#include "List.h"

class Builder
{
private:
	map<string, Term*> _termMap;
public:
	Builder();
	~Builder();
	
	Atom* getAtomInstance(string symbol);
	Variable* getVariableInstance(string symbol);
	Number* getNumberInstance(string symbol);
	Struct* getStructInstance(Atom name, vector<Term*> childs);
	List* getListInstance(vector<Term *> elements);
};

