#pragma once
#include <iostream>
using namespace std;

class Leaf
{
private:
	string _tokenType;
	string _tokenValue;
public:
	Leaf(string tokenType, string tokenValue);
	~Leaf();
	string getTokenType();
	string getTokenValue();
};

