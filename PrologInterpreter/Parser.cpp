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


	Leaf* leaf = _scanner->peekNextLeaf();
	if (leaf->getTokenType() == "EndOfClause")
	{
		root = operateor;
	}
	else if (leaf->getTokenType() == "Comma")
	{
		root = new Node(COMMA, nullptr, operateor, this->createTree());
	}
	return root;
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
		term = new Variable(leaf->getTokenValue());
	}
	else if (leaf->getTokenType() == "Number")
	{
		_scanner->getNextLeaf();
		term = new Number(leaf->getTokenValue());
	}
	else if (leaf->getTokenType() == "Atom")
	{
		_scanner->getNextLeaf();
		Atom* atom = new Atom(leaf->getTokenValue());
		term = atom;
		Leaf* next = _scanner->peekNextLeaf();
		if (next->getTokenType() == "StructBegin")
		{
			_scanner->getNextLeaf();
			term = new Struct(*atom, this->getArgs());
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
		term = new List(this->getArgs());
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
