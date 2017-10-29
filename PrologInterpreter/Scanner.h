#pragma once
#include <iostream>
#include "Leaf.h"
#include <regex>
using namespace std;

class Scanner
{
private:
	
	string _inputString;
public:
	Scanner(string inputString);
	~Scanner();
	Leaf* getNextLeaf();
};