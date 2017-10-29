#include "Scanner.h"



Scanner::Scanner(string inputString) :_inputString(inputString)
{
}


Scanner::~Scanner()
{
}

Leaf * Scanner::getNextLeaf()
{
	Leaf* leaf = NULL;
	smatch sm;
	regex variableRegex("^[A-Z_][A-Za-z0-9_]*");
	regex atomRegex("^[a-z_][A-Za-z0-9_]*");
	if (regex_search(_inputString, sm, variableRegex)) {
		leaf = new Leaf("Variable", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, atomRegex))
	{
		leaf = new Leaf("Atom", sm.str());
		_inputString = sm.suffix();
	}
	return leaf;
}
