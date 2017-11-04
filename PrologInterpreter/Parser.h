#pragma once
#include "Scanner.h"
#include "Term.h"
#include "Variable.h"
#include "Number.h"
#include "Atom.h"
#include "Struct.h"
#include "List.h"
#include <vector>

class Parser
{
private:
	Scanner* _scanner;
public:
	Parser(Scanner& scanner);
	~Parser();
	Term* createTerm();
	vector<Term*> getArgs();
};

