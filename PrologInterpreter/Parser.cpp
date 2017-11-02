#include "Parser.h"

Parser::Parser(Scanner & scanner) :_scanner(&scanner)
{

}

Parser::~Parser()
{
}

Term * Parser::createTerm()
{
	Leaf* leaf = _scanner->getNextLeaf();
	Term* term = NULL;
	if (leaf->getTokenType() == "Variable")
	{
		term = new Variable(leaf->getTokenValue());
	}
	return term;
}
