#pragma once
#include <iostream>
#include "Leaf.h"
#include <regex>
#include <list>
#include <map>
#include <sstream>
using namespace std;

class Scanner
{
private:
	static map<string, regex> _regexMap;
	static list<pair<string, regex>> _regexs;
	string _inputString;
public:
	Scanner(string inputString="");
	~Scanner();
	Leaf* getNextLeaf();
	Leaf* peekNextLeaf();
};