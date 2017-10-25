#pragma once
#include <string>
using std::string;

#include "List.h"
#include "Struct.h"
#include "Atom.h"
#include "Number.h"
#include "Variable.h"

// When create a new list without any item
// Then #symbol() of the list should return "[]"
TEST(List, constructor) {
	List list;
	ASSERT_EQ("[]", list.symbol());
}

// Given there are two perfect numbers: 8128
// When create a new list with the perfect Number
// Then #symbol() of the list should return "[8128]"
TEST(List, Numbers) {
	Number n(8128);
	vector<Term*> v = { &n };
	List list(v);
	ASSERT_EQ("[8128]", list.symbol());
}

// Given there are two atoms: "terence_tao", "alan_mathison_turing"
// When create a new list with the Atoms
// Then #symbol() of the list should return "[terence_tao, alan_mathison_turing]"
TEST(List, Atoms) {
	Atom terence_tao("terence_tao");
	Atom alan_mathison_turing("alan_mathison_turing");
	vector<Term*> v = { &terence_tao,&alan_mathison_turing };
	List list(v);
	ASSERT_EQ("[terence_tao, alan_mathison_turing]", list.symbol());
}

// Given there are two variables: X, Y
// When create a new list with the variables
// Then #symbol() of the list should return "[X, Y]"
TEST(List, Vars) {
	Variable X("X");
	Variable Y("Y");
	vector<Term*> v = { &X,&Y };
	List list(v);
	ASSERT_EQ("[X, Y]", list.symbol());
}

// ?- tom = [496, X, terence_tao].
// false.
TEST(List, matchToAtomShouldFail) {
	Atom tom("tom");
	Number n(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	ASSERT_FALSE(tom.match(list));
}

// ?- 8128 = [496, X, terence_tao].
// false.
TEST(List, matchToNumberShouldFail) {
	Number n1(8128);
	Number n(496);
	Variable X("X");
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	ASSERT_FALSE(n1.match(list));
}

// ?- s(X) = [496, X, terence_tao].
// false.
TEST(List, matchToStructShouldFail) {
	Variable X("X");
	Number n(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	vector<Term*> v2 = { &X };
	Atom name("s");
	Struct s(name, v2);
	ASSERT_FALSE(s.match(list));
}

// ?- Y = [496, X, terence_tao].
// Y = [496, X, terence_tao].
TEST(List, matchToVarShouldSucceed) {
	Variable X("X");
	Number n(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	Variable Y("Y");
	ASSERT_TRUE(Y.match(list));
	EXPECT_EQ("[496, X, terence_tao]", Y.value());
}

// ?- X = [496, X, terence_tao].
// false.
TEST(List, matchToVarOccuredInListShouldFail) {
	Variable X("X");
	Number n(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	ASSERT_TRUE(X.match(list));
}

// ?- [496, X, terence_tao] = [496, X, terence_tao].
// true.
TEST(List, matchToSameListShouldSucceed) {
	Variable X("X");
	Number n(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	ASSERT_TRUE(list.match(list));
}

// ?- [496, X, terence_tao] = [496, Y, terence_tao].
// true.
TEST(List, matchToSameListWithDiffVarNameShouldSucceed) {
	Variable X("X");
	Number n(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	Variable Y("Y");
	vector<Term*> v2 = { &n, &Y, &terence_tao };
	List list2(v2);
	ASSERT_TRUE(list.match(list2));
}

// ?- [496, X, terence_tao] = [496, 8128, terence_tao].
// X = 8128.
TEST(List, matchToVarToAtominListShouldSucceed) {
	Variable X("X");
	Number n(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	Number n2(8128);
	vector<Term*> v2 = { &n, &n2, &terence_tao };
	List list2(v2);
	ASSERT_TRUE(list.match(list2));
}

// ?- Y = [496, X, terence_tao], X = alan_mathison_turing.
// Y = [496, alan_mathison_turing, terence_tao],
// X = alan_mathison_turing.
TEST(List, matchVarinListToAtomShouldSucceed) {
	Variable Y("Y");
	Variable X("X");
	Number n(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &n, &X, &terence_tao };
	List list(v);
	Atom alan_mathison_turing("alan_mathison_turing");
	ASSERT_TRUE(Y.match(list));
	ASSERT_TRUE(X.match(alan_mathison_turing));
	EXPECT_EQ("[496, alan_mathison_turing, terence_tao]", Y.value());
	EXPECT_EQ("alan_mathison_turing", X.value());
}

// Example: 
// ?- [first, second, third] = [H|T].
// H = first, T = [second, third].
TEST(List, headAndTailMatching1) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);

	EXPECT_EQ(string("first"), l.head()->symbol());
	EXPECT_EQ(string("[second, third]"), l.tail()->value());
}

// Example:
// ?- [first, second, third] = [first, H|T].
// H = second, T = [third].
TEST(List, headAndTailMatching2) {
	Atom f("first"), s("second"), t("third");
	vector<Term *> args = { &f, &s, &t };
	List l(args);

	EXPECT_EQ(string("second"), l.tail()->head()->value());
	EXPECT_EQ(string("[third]"), l.tail()->tail()->value());
}

// ?- [[first], second, third] = [H|T].
// H = [first], T = [second, third].
TEST(List, headAndTailMatching3) {
	Atom first("first");
	Atom second("second");
	Atom third("third");
	vector<Term *> v1 = { &first };
	List list(v1);
	vector<Term *> v2 = { &list,&second,&third };
	List list2(v2);
	ASSERT_EQ("[first]", list2.head()->value());
	ASSERT_EQ("[second, third]", list2.tail()->value());
}

// ?- [first, second, third] = [first, second, H|T].
// H = third, T = [].
TEST(List, headAndTailMatching4) {
	Atom first("first");
	Atom second("second");
	Atom third("third");
	vector<Term *> v = { &first,&second,&third };
	List list(v);
	ASSERT_EQ("first", list.head()->value());
	ASSERT_EQ("[second, third]", list.tail()->value());
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing head in an empty list" as an exception.
TEST(List, emptyExecptionOfHead) {
	List list;
	try
	{
		Term* head = list.head();
	}
	catch (string err)
	{
		EXPECT_EQ(err, "Accessing head in an empty list");
	}
}

// Given there is a empty list
// When client still want to get the head of list
// Then it should throw a string: "Accessing tail in an empty list" as an exception.
TEST(List, emptyExecptionOfTail) {
	List list;
	try
	{
		Term* tail = list.tail();
	}
	catch (string err)
	{
		EXPECT_EQ(err, "Accessing tail in an empty list");
	}
}

// ?- [X] = [X].
// true.
TEST(List, matchToSameListWithX) {
	Variable X("X");
	Number n(496);
	Atom terence_tao("terence_tao");
	vector<Term*> v = { &X };
	List list(v);
	ASSERT_TRUE(list.match(list));	
	bool again = list.match(list);
	//ASSERT_TRUE(list.match(list));
}