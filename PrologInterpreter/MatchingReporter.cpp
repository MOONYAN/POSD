#include "MatchingReporter.h"



string MatchingReporter::combineAndLayer(map<string, Variable*> termMap)
{
	stringstream ss;
	bool isBegin = true;
	for (auto pair : termMap)
	{
		string symbol = pair.first;
		string value = pair.second->value();
		if (symbol != value)
		{
			if (isBegin)
			{
				isBegin = false;
			}
			else
			{
				ss << ", ";
			}
			ss << symbol << " = " << value;
		}
	}
	return ss.str();
}

string MatchingReporter::combineOrLayer(list<map<string, Variable*>> termMaps)
{
	stringstream ss;
	bool isBegin = true;
	for (auto termMap : termMaps)
	{
		string andResult = combineAndLayer(termMap);
		if (andResult != "")
		{
			if (isBegin)
			{
				isBegin = false;
			}
			else
			{
				ss << "; ";
			}
			ss << andResult;
		}
	}
	return ss.str();
}

MatchingReporter::MatchingReporter()
{

}


MatchingReporter::~MatchingReporter()
{
}

string MatchingReporter::getResult()
{
	stringstream ss;
	if (_termMaps.size() == 0)
	{
		ss << "false.";
	}
	else
	{
		string orResult = combineOrLayer(_termMaps);
		if (orResult != "")
		{
			ss << orResult << ".";
		}
		else
		{
			ss << "true.";
		}
	}	
	return ss.str();
}

void MatchingReporter::clearPool()
{
	_termMap.clear();
}

void MatchingReporter::nextLayer()
{
	_termMaps.push_back(_termMap);
	_termMap = map<string, Variable*>();
}

void MatchingReporter::watchVariable(Variable * variable)
{
	string symbol = variable->symbol();
	if (_termMap[symbol] == nullptr)
	{
		_termMap[symbol] = variable;
	}
}
