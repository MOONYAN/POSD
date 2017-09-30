#pragma once
#include "Number.h"
#include "Atom.h"

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
	ASSERT_TRUE(number.match(&number));
	Number newNumber(25);
	ASSERT_TRUE(number.match(&newNumber));
}

//?- 25=0.
//false.
TEST(Number, matchFailureDiffValue) {
	Number number(25);
	Number other(0);
	ASSERT_FALSE(number.match(&other));
}

//?- 25=tom.
//false.
TEST(Number, matchFailureDiffConstant) {
	Number number(25);
	Atom tom("tom");
	ASSERT_FALSE(number.match(&tom));
}

////?- 25=X.
////true.
//TEST(Number, matchSuccessToVar) {
//
//}
//
////?- tom=25.
////false.
//TEST(Atom, matchFailureDiffConstant) {
//
//}
//
//// ?- tom = X.
//// X = tom.
//TEST(Atom, matchSuccessToVar) {
//
//}
//
//// ?- X=tom, tom=X.
//// X = tom.
//TEST(Atom, matchSuccessToVarInstantedToDiffConstant) {
//
//}
//
//// ?- X=jerry, tom=X.
//// false.
//TEST(Atom, matchFailureToVarInstantedToDiffConstant) {
//
//}
//
//// ?- X = 5.
//// X = 5.
//TEST(Var, matchSuccessToNumber) {
//
//}
//
//// ?- X=25, X= 100.
//// false.
//TEST(Var, matchFailureToTwoDiffNumbers) {
//
//}
//
//// ?- X=tom, X= 25.
//// false.
//TEST(Var, matchSuccessToAtomThenFailureToNumber) {
//
//}
//
////?- tom=X, 25=X.
////false.
//TEST(Var, matchSuccessToAtomThenFailureToNumber2) {
//
//}
//
////?- X=tom, X=tom.
////true.
//TEST(Var, reAssignTheSameAtom) {
//
//}