#include "Scanner.h"
#include "Parser.h"
#include "MatchingReporter.h"
#include <iostream>
#include <regex>

using namespace std;

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
		Scanner s(clause);
		Parser p(s);
		try {
			p.buildExpression();
			MatchingReporter reporter;
			p.getExpressionTree()->evaluate(&reporter);
			string result = reporter.getResult();
			cout << result << endl;
		}
		catch (std::string &msg) {
			cout << msg << endl;
		}
	};

	for (cout << "?-", cin >> input; !isMatchHalt(); cin >> input)
	{
		if (isEndOfClause())
		{
			ss << input;
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
	cout << "exit" << endl;

	return 0;
}