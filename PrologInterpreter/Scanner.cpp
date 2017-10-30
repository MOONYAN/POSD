#include "Scanner.h"



Scanner::Scanner(string inputString) :_inputString(inputString)
{
}


Scanner::~Scanner()
{
}

Leaf * Scanner::getNextLeaf()
{
	Leaf* leaf = NULL ;
	smatch sm;

	for each (auto pair in _regexMap)
	{
		const string& tokenType = pair.first;
		regex& regexPattern = pair.second;
		if (regex_search(_inputString, sm, regexPattern)) {
			leaf = new Leaf(tokenType, sm.str());
			_inputString = sm.suffix();
			break;
		}
	}
	return leaf;
}

map<string, regex> Scanner::_regexMap = {
	{ "Variable", regex({ "^[A-Z_]\\w*" }) },
	{ "Atom", regex({ "^[a-z]\\w*" }) },
	{ "Number", regex({ "^(\\+|-)?(\\d+(\\.\\d+)?)" }) },
	{ "Comma", regex({ "^," }) },
	{ "Match", regex({ "^=" }) },
	{ "ListBegin", regex({ "^\\[" }) },
	{ "ListEnd", regex({ "^\\]" }) },
	{ "StructBegin", regex({ "^\\(" }) },
	{ "StructEnd", regex({ "^\\)" }) }
};