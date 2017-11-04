#pragma once
#include <iostream>
#include "Leaf.h"
#include <regex>
#include <map>
#include <sstream>
using namespace std;

class Scanner
{
private:
	static map<string, regex> _regexMap;
	string _inputString;
public:
	Scanner(string inputString);
	~Scanner();
	Leaf* getNextLeaf();
};