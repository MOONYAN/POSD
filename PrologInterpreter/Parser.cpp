#include "Parser.h"

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
}

Node * Parser::expressionTree()
{
	return nullptr;
}
