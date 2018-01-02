#include "../PrologInterpreter/Scanner.h"
#include "../PrologInterpreter/Parser.h"
#include "../PrologInterpreter/MatchingReporter.h"
#include <iostream>
#include <regex>

int main()
{
	string input;
	stringstream ss;

	auto isMatchHalt = [&]() {
		return regex_search(input, regex({ "^halt\\.$" }));
	};

	auto isEndOfClause = [&]() {
		return regex_search(input, regex({ "\\.$" }));
	};

	auto tryExexute = [](string clause) {
		cout << clause << endl;
	};

	for (cout << "?-", cin >> input; !isMatchHalt(); cin >> input)
	{
		if (isEndOfClause())
		{
			tryExexute(ss.str());
			ss = stringstream();
			cout << "?-";
		}
		else
		{
			ss << input;
			cout << "| ";
		}
	}
	cout << "exit";

	return 0;
}