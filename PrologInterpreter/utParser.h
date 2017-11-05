#pragma once
#include "Parser.h"
#include "Scanner.h"
#include "Term.h"
#include "List.h"
#include "Variable.h"
#include "Number.h"

TEST(ParserTest, createTerm_Var) {
	Scanner scanner("X");
	Parser parser(scanner);
	ASSERT_EQ("X", parser.createTerm()->symbol());
}

TEST(ParserTest, createTerm_Num) {
	Scanner scanner("123");
	Parser parser(scanner);
	ASSERT_EQ("123", parser.createTerm()->symbol());
}

TEST(ParserTest, createTerm_Atom)
{
	Scanner scanner("tom");
	Parser parser(scanner);
	ASSERT_EQ("tom", parser.createTerm()->symbol());
}

TEST(ParserTest, createArgs)
{
	Scanner scanner("1, X, tom");
	Parser parser(scanner);
	vector<Term*> terms = parser.getArgs();
	ASSERT_EQ("1", terms[0]->symbol());
	ASSERT_EQ("X", terms[1]->symbol());
	ASSERT_EQ("tom", terms[2]->symbol());
}

TEST(ParserTest, createTerms)
{
	Scanner scanner("s(1, X, tom)");
	Parser parser(scanner);
	ASSERT_EQ("s(1, X, tom)", parser.createTerm()->symbol());
}


// Given there is string: " 12345,  tom" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "tom".
TEST(ParserTest, listOfTermsTwo) {
	Scanner scanner(" 12345,  tom");
	Parser parser(scanner);
	vector<Term*> terms = parser.getArgs();
	ASSERT_EQ("12345", terms[0]->symbol());
	ASSERT_EQ("tom", terms[1]->symbol());
}


// Given there is string: "point(1, X, z(1,2,3))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z(1,2,3))".
TEST(ParserTest, parseStructOfStruct) {
	Scanner scanner("point(1, X, z(1,2,3))");
	Parser parser(scanner);
	ASSERT_EQ("point(1, X, z(1, 2, 3))", parser.createTerm()->symbol());
}


// Given there is string: " 12345,  67" in scanner.
// When parser parses all terms via scanner.
// Then it should return two terms, one is "12345", another is "67".
TEST(ParserTest, listOfTermsTwoNumbers) {
	Scanner scanner(" 12345,  67");
	Parser parser(scanner);
	vector<Term*> terms = parser.getArgs();
	ASSERT_EQ("12345", terms[0]->symbol());
	ASSERT_EQ("67", terms[1]->symbol());
}


// Given there is string: "point(1, X, z)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(1, X, z)".
TEST(ParserTest, parseStructThreeArgs) {
	Scanner scanner("point(1, X, z)");
	Parser parser(scanner);
	ASSERT_EQ("point(1, X, z)", parser.createTerm()->symbol());
}


// Given there is string: "   [   ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[]".
TEST(ParserTest, parseListEmpty) {
	Scanner scanner("   [   ]");
	Parser parser(scanner);
	ASSERT_EQ("[]", parser.createTerm()->symbol());
}


// Given there is string: "_date" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Variable.
// And #symbol() of Variable should return "_date".
TEST(ParserTest, parseVar) {
	Scanner scanner("_date");
	Parser parser(scanner);
	ASSERT_EQ("_date", parser.createTerm()->symbol());
}


// Given there is not string in scanner.
// When parser parses all terms via scanner.
// Then it should return nothing.
TEST(ParserTest, listOfTermsEmpty) {
	Scanner scanner;
	Parser parser(scanner);
	ASSERT_EQ(nullptr, parser.createTerm());
}


// Given there is string: "s(s(s(s(1))))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "s(s(s(s(1))))".
TEST(ParserTest, parseStructOfStructAllTheWay) {
	Scanner scanner("s(s(s(s(1))))");
	Parser parser(scanner);
	ASSERT_EQ("s(s(s(s(1))))", parser.createTerm()->symbol());
}


// Given there is string: "   [  [1], [] ]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], []]".
TEST(ParserTest, parseListOfLists) {
	Scanner scanner("   [  [1], [] ]");
	Parser parser(scanner);
	ASSERT_EQ("[[1], []]", parser.createTerm()->symbol());
}


// Given there is string: "   [  [1], [], s(s(1)) ]   " in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[[1], [], s(s(1))]".
TEST(ParserTest, parseListOfListsAndStruct) {
	Scanner scanner("   [  [1], [], s(s(1)) ]   ");
	Parser parser(scanner);
	ASSERT_EQ("[[1], [], s(s(1))]", parser.createTerm()->symbol());
}

// Given there is string: "   [1, 2]" in scanner.
// When parser parses all terms via scanner.
// Then it should return a List.
// And #symbol() of List should return "[1, 2]".
TEST(ParserTest, parseList) {
	Scanner scanner("   [1, 2]");
	Parser parser(scanner);
	ASSERT_EQ("[1, 2]", parser.createTerm()->symbol());
}

// Given there is string: "[1,2)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a string: "unexpected token" as exception.
TEST(ParserTest, illegal1) {
	Scanner scanner("   [1,2)");
	Parser parser(scanner);
	try
	{
		parser.createTerm();
	}
	catch (string error)
	{
		ASSERT_EQ("unexpected token", error);
	}
}

// Given there is string: ".(1,[])" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(1, [])".
// And the first term should be number: "1", the second term should be another List: "[]".
TEST(ParserTest, ListAsStruct) {
	Scanner scanner(".(1,[])");
	Parser parser(scanner);
	Struct* term = dynamic_cast<Struct*> (parser.createTerm());
	ASSERT_EQ(".(1, [])", term->symbol());
	ASSERT_EQ(2, term->arity());
}


// Given there is string: ".(2,.(1,[]))" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct which contains two terms.
// And #arity() of the Struct should be 2.
// And #symbol() of Struct should return ".(2, .(1, []))"
// And the first term should be number: "2", the second term should be another Strcut: ".(1, [])".
TEST(ParserTest, ListAsStruct2) {
	Scanner scanner(".(2,.(1,[]))");
	Parser parser(scanner);
	Struct* term = dynamic_cast<Struct*> (parser.createTerm());
	ASSERT_EQ(2, term->arity());
	ASSERT_EQ(".(2, .(1, []))", term->symbol());
	ASSERT_EQ("2",term->args(0)->symbol());
	ASSERT_EQ(".(1, [])", term->args(1)->symbol());
}


// Given there is string: "s(s(s(s(1)))), b(1,2,3)" in scanner.
// When parser parses all terms via scanner.
// Then it should return two Struct.
// And #symbol() of the first Strcut should return "s(s(s(s(1))))".
// And #symbol() of the second Strcut should return "b(1, 2, 3)".
TEST(ParserTest, parseStructOfStructAllTheWay2) {
	Scanner scanner("s(s(s(s(1)))), b(1,2,3)");
	Parser parser(scanner);
	vector<Term*> terms = parser.getArgs();
	ASSERT_EQ("s(s(s(s(1))))", terms[0]->symbol());
	ASSERT_EQ("b(1, 2, 3)", terms[1]->symbol());
}


// Given there is string: "point()" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point()".
TEST(ParserTest, parseStructNoArg) {
	Scanner scanner("point()");
	Parser parser(scanner);
	Struct* term = dynamic_cast<Struct*> (parser.createTerm());
	ASSERT_EQ("point()", term->symbol());
}


// Given there is string: " 12345,  tom,   Date" in scanner.
// When parser parses all terms via scanner.
// Then it should return three terms: "12345", "tom" and "Date".
TEST(ParserTest, listOfTermsThree) {
	Scanner scanner(" 12345,  tom,   Date");
	Parser parser(scanner);
	vector<Term*> terms = parser.getArgs();
	ASSERT_EQ("12345", terms[0]->symbol());
	ASSERT_EQ("tom", terms[1]->symbol());
	ASSERT_EQ("Date", terms[2]->symbol());
}


// Given there is string: "point(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11, 12)".
TEST(ParserTest, parseStructTwoArgs) {
	Scanner scanner("point(11,12)");
	Parser parser(scanner);
	Struct* term = dynamic_cast<Struct*> (parser.createTerm());
	ASSERT_EQ("point(11, 12)", term->symbol());
}


// Given there is string: "...(11,12)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "...(11, 12)".
TEST(ParserTest, parseStructDOTSTwoArgs) {
	Scanner scanner("...(11,12)");
	Parser parser(scanner);
	ASSERT_EQ("...(11, 12)", parser.createTerm()->symbol());
}


// Given there is string: "point(11)" in scanner.
// When parser parses all terms via scanner.
// Then it should return a Struct.
// And #symbol() of Strcut should return "point(11)".
TEST(ParserTest, parseStructOneArg) {
	Scanner scanner("point(11)");
	Parser parser(scanner);
	Struct* term = dynamic_cast<Struct*> (parser.createTerm());
	ASSERT_EQ("point(11)", term->symbol());
}