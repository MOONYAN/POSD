#pragma once
#include <sstream>
#include <list>
#include <map>
#include "Variable.h"

using namespace std;

class MatchingReporter
{
private:
	list<map<string, Variable*>> _termMaps;
	map<string, Variable*> _termMap;

	string combineAndLayer(map<string, Variable*> termMap);
	string combineOrLayer(list<map<string, Variable*>> termMaps);
public:
	MatchingReporter();
	~MatchingReporter();

	string getResult();
	void clearPool();
	void nextLayer();
	void watchVariable(Variable* variable);
};

