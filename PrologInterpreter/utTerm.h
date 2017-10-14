#pragma once
#include "Number.h"
#include "Atom.h"
#include "Variable.h"

//test Number.value()
TEST(Number, ctor) {
	Number one(1);
	ASSERT_EQ("1", one.value());
}

//test Number.symbol()
TEST(Number, symbol) {
	Number one(1);
	ASSERT_EQ("1", one.symbol());
}

//?- 25=25.
//true.
TEST(Number, matchSuccess) {
	Number number(25);
	Number other(25);
	ASSERT_TRUE(number.match(other));
}

//?- 25=0.
//false.
TEST(Number, matchFailureDiffValue) {
	Number number(25);
	Number other(0);
	ASSERT_FALSE(number.match(other));
}

//?- 25=tom.
//false.
TEST(Number, matchFailureDiffConstant) {
	Number number(25);
	Atom tom("tom");
	ASSERT_FALSE(number.match(tom));
}

//?- 25=X.
//true.
TEST(Number, matchSuccessToVar) {
	Number number(25);
	Variable X("X");
	ASSERT_TRUE(number.match(X));
	EXPECT_EQ("25", X.value());
}

//?- tom=25.
//false.
TEST(Atom, matchFailureDiffConstant) {
	Atom tom("tom");
	Number number(25);
	ASSERT_FALSE(tom.match(number));
}

// ?- tom = X.
// X = tom.
TEST(Atom, matchSuccessToVar) {
	Atom tom("tom");
	Variable X("X");
	ASSERT_TRUE(tom.match(X));
	EXPECT_EQ("tom", X.value());
}

// ?- X=tom, tom=X.
// X = tom.
TEST(Atom, matchSuccessToVarInstantedToDiffConstant) {
	Variable X("X");
	Atom tom("tom");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(tom.match(X));
	EXPECT_EQ("tom", X.value());
}

// ?- X=jerry, tom=X.
// false.
TEST(Atom, matchFailureToVarInstantedToDiffConstant) {
	Variable X("X");
	Atom jerry("jerry");
	Atom tom("tom");
	ASSERT_TRUE(X.match(jerry));
	EXPECT_FALSE(tom.match(X));
}

// ?- X = 5.
// X = 5.
TEST(Variable, matchSuccessToNumber) {
	Variable X("X");
	Number number(5);
	ASSERT_TRUE(X.match(number));
	EXPECT_EQ("5", X.value());
}

// ?- X=25, X= 100.
// false.
TEST(Variable, matchFailureToTwoDiffNumbers) {
	Variable X("X");
	Number number1(25);
	Number number2(100);
	ASSERT_TRUE(X.match(number1));
	EXPECT_FALSE(X.match(number2));
	EXPECT_EQ("25", X.value());
}

// ?- X=tom, X= 25.
// false.
TEST(Variable, matchSuccessToAtomThenFailureToNumber) {
	Variable X("X");
	Atom tom("tom");
	Number number(25);
	ASSERT_TRUE(X.match(tom));
	EXPECT_FALSE(X.match(number));
}

//?- tom=X, 25=X.
//false.
TEST(Variable, matchSuccessToAtomThenFailureToNumber2) {
	Atom tom("tom");
	Variable X("X");
	Number number(25);
	ASSERT_TRUE(tom.match(X));
	EXPECT_FALSE(number.match(X));
}

//?- X=tom, X=tom.
//true.
TEST(Variable, reAssignTheSameAtom) {
	Variable X("X");
	Atom tom("tom");
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(X.match(tom));
}

//?- X=tom, X=tom.
//true.
TEST(Variable, matchSelf) {
	Variable X("X");
	Atom tom("tom");
	Number number(1);
	ASSERT_TRUE(X.match(X));
	ASSERT_TRUE(X.match(tom));
	ASSERT_TRUE(tom.match(tom));
	ASSERT_TRUE(number.match(number));
}