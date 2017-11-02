#pragma once
#include "Scanner.h"
#include "Term.h"
#include "Variable.h"
#include "Number.h"
#include "Atom.h"

class Parser
{
private:
	Scanner* _scanner;
public:
	Parser(Scanner& scanner);
	~Parser();
	Term* createTerm();
};

