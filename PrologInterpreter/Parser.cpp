#include "Parser.h"

Node * Parser::createTree()
{
	Node* root = nullptr;
	Term* term = nullptr;
	term = this->createTerm();
	_terms.push_back(term);
	Node* left = new Node(TERM, term, nullptr, nullptr);
	//expect =
	_scanner->getNextLeaf();
	Node* operateor = new Node(EQUALITY);
	term = this->createTerm();
	_terms.push_back(term);
	Node* right = new Node(TERM, term, nullptr, nullptr);
	operateor->left = left;
	operateor->right = right;


	Leaf* leaf = _scanner->getNextLeaf();
	if (leaf->getTokenType() == "EndOfClause")
	{
		root = operateor;
	}
	else if (leaf->getTokenType() == "Comma")
	{
		root = new Node(COMMA, nullptr, operateor, this->createTree());
	}
	else if (leaf->getTokenType() == "Semicolon")
	{
		_builder.clearPool();
		root = new Node(SEMICOLON, nullptr, operateor, this->createTree());
	}
	return root;
}

void Parser::disjunctionMatch()
{
	_builder.clearPool();
	conjunctionMatch();
	restConjunctionMatch();
}

void Parser::restDisjunctionMatch()
{
	if (_scanner->peekNextLeaf()->getTokenType() == "Semicolon") {
		_scanner->getNextLeaf();
		disjunctionMatch();
		restDisjunctionMatch();
		Exp* right = _expStack.top();
		_expStack.pop();
		Exp* left = _expStack.top();
		_expStack.pop();
		_expStack.push(new DisjExp(left, right));
	}	
}

void Parser::conjunctionMatch()
{
	Term* left = createTerm();
	if (left == nullptr) {
		throw string("Missing token 'Term'");
	}
	if (_scanner->getNextLeaf()->getTokenType() != "Match") {
		throw string("Missing token '='");
	}
	Term* right = createTerm();
	if (right == nullptr) {
		throw string("Missing token 'Term'");
	}
	_expStack.push(new MatchExp(left, right));
}

void Parser::restConjunctionMatch()
{
	if (_scanner->peekNextLeaf()->getTokenType() == "Comma") {
		_scanner->getNextLeaf();
		conjunctionMatch();
		restConjunctionMatch();
		Exp* right = _expStack.top();
		_expStack.pop();
		Exp* left = _expStack.top();
		_expStack.pop();
		_expStack.push(new ConjExp(left, right));
	}
}

Parser::Parser(Scanner & scanner) :_scanner(&scanner)
{

}

Parser::~Parser()
{
}

Term * Parser::createTerm()
{

	Leaf* leaf = _scanner->peekNextLeaf();
	Term* term = nullptr;
	if (leaf->getTokenType() == "Variable")
	{
		_scanner->getNextLeaf();
		term = _builder.getVariableInstance(leaf->getTokenValue());
	}
	else if (leaf->getTokenType() == "Number")
	{
		_scanner->getNextLeaf();
		term = _builder.getNumberInstance(leaf->getTokenValue());
	}
	else if (leaf->getTokenType() == "Atom")
	{
		_scanner->getNextLeaf();
		Atom* atom = _builder.getAtomInstance(leaf->getTokenValue());
		term = atom;
		Leaf* next = _scanner->peekNextLeaf();
		if (next->getTokenType() == "StructBegin")
		{
			_scanner->getNextLeaf();
			term = _builder.getStructInstance(*atom, this->getArgs());
			//expect )
			if (_scanner->getNextLeaf()->getTokenType() != "StructEnd")
			{
				throw string("unexpected token");
			}
		}
	}
	else if (leaf->getTokenType() == "ListBegin")
	{
		_scanner->getNextLeaf();
		term = _builder.getListInstance(this->getArgs());
		//expect ]
		if (_scanner->getNextLeaf()->getTokenType() != "ListEnd")
		{
			throw string("unexpected token");
		}
	}
	return term;
}

vector<Term*> Parser::getArgs()
{
	vector<Term*> args;
	//Leaf* leaf = _scanner->peekNextLeaf();
	do
	{
		Term* term = createTerm();
		if (term == nullptr)
		{
			break;
		}
		args.push_back(term);
		Leaf* peekLeaf = _scanner->peekNextLeaf();
		if (peekLeaf->getTokenType() != "Comma")
			break;
		else
			_scanner->getNextLeaf();
	} while (true);
	return args;
}

void Parser::createTerms()
{
	_terms = getArgs();
}

vector<Term*>& Parser::getTerms()
{
	return _terms;
}

void Parser::matchings()
{
	_terms = vector<Term*>();
	_treeRoot = createTree();
}

Node * Parser::expressionTree()
{
	return _treeRoot;
}

void Parser::buildExpression()
{
	disjunctionMatch();
	restDisjunctionMatch();
	if (_scanner->getNextLeaf()->getTokenType() != "EndOfClause")
	{
		throw string("Missing token '.'");
	}
}

Exp * Parser::getExpressionTree()
{
	return _expStack.top();
}
