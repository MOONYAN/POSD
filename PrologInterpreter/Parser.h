#pragma once
#include "Scanner.h"
#include "Term.h"
#include "Variable.h"
#include "Number.h"
#include "Atom.h"
#include "Struct.h"
#include "List.h"
#include "Node.h"
#include <vector>

class Parser
{
private:
	Scanner* _scanner;
	vector<Term *> _terms;
	Node* _treeRoot;
	Node* createTree();
public:
	Parser(Scanner& scanner);
	~Parser();
	Term* createTerm();
	vector<Term*> getArgs();
	void createTerms();
	vector<Term *> & getTerms();
	void matchings();
	Node* expressionTree();
};

