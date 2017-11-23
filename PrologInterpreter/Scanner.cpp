#include "Scanner.h"



Scanner::Scanner(string inputString)
{
	stringstream ss;
	ss << regex_replace(inputString, regex({"\\s"}), "");
	ss >> _inputString;
}


Scanner::~Scanner()
{
}

Leaf * Scanner::getNextLeaf()
{
	Leaf* leaf = NULL;
	smatch sm;

	for (auto pair : _regexs)
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

Leaf * Scanner::peekNextLeaf()
{
	Leaf* leaf = NULL;
	smatch sm;

	for (auto pair : _regexs)
	{
		const string& tokenType = pair.first;
		regex& regexPattern = pair.second;
		if (regex_search(_inputString, sm, regexPattern)) {
			leaf = new Leaf(tokenType, sm.str());
			break;
		}
	}
	return leaf;
}

list<pair<string, regex>> Scanner::_regexs = {
	{ "EndOfClause", regex({ "^\\.$" }) },
	{ "Variable", regex({ "^[A-Z_]\\w*" }) },
	{ "Atom", regex({ "^[.a-z][.a-zA-z0-9_]*" }) },
	{ "Number", regex({ "^(\\+|-)?(\\d+(\\.\\d+)?)" }) },
	{ "Comma", regex({ "^," }) },
	{ "Match", regex({ "^=" }) },
	{ "ListBegin", regex({ "^\\[" }) },
	{ "ListEnd", regex({ "^\\]" }) },
	{ "StructBegin", regex({ "^\\(" }) },
	{ "StructEnd", regex({ "^\\)" }) },
	{ "EndOfString", regex({ "^$" }) }
};