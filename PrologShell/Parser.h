#pragma once
#include "Scanner.h"
#include "Term.h"
#include "Variable.h"
#include "Number.h"
#include "Atom.h"
#include "Struct.h"
#include "List.h"
#include "Node.h"
#include "Builder.h"
#include "Exp.h"
#include <stack>
#include <vector>

class Parser
{
private:
	Builder _builder;
	Scanner* _scanner;
	vector<Term *> _terms;
	stack<Exp*> _expStack;
	Node* _treeRoot;
	Node* createTree();
	void disjunctionMatch();
	void restDisjunctionMatch();
	void conjunctionMatch();
	void restConjunctionMatch();
public:
	Parser(Scanner& scanner);
	~Parser();
	Term* createTerm();
	vector<Term*> getArgs();
	void createTerms();
	vector<Term *> & getTerms();
	void matchings();
	Node* expressionTree();
	void buildExpression();
	Exp* getExpressionTree();
};

