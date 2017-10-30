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
	//^[A-Z_]\w*
	regex variableRegex({ "^[A-Z_]\\w*" });
	//^[a-z]\w*
	regex atomRegex({ "^[a-z]\\w*" });
	//^(\+|-)?(\d+(\.\d+)?)
	regex numberRegex({ "^(\\+|-)?(\\d+(\\.\\d+)?)" });
	if (regex_search(_inputString, sm, variableRegex)) {
		leaf = new Leaf("Variable", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, atomRegex))
	{
		leaf = new Leaf("Atom", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, numberRegex))
	{
		leaf = new Leaf("Number", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, regex({ "^," })))
	{
		leaf = new Leaf("Comma", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, regex({ "^=" })))
	{
		leaf = new Leaf("Match", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, regex({ "^\\[" })))
	{
		leaf = new Leaf("ListBegin", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, regex({ "^\\]" })))
	{
		leaf = new Leaf("ListEnd", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, regex({ "^\\(" })))
	{
		leaf = new Leaf("StructBegin", sm.str());
		_inputString = sm.suffix();
	}
	else if (regex_search(_inputString, sm, regex({ "^\\)" })))
	{
		leaf = new Leaf("StructEnd", sm.str());
		_inputString = sm.suffix();
	}

	return leaf;
}
