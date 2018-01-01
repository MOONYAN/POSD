#pragma once

#include "Term.h"
#include "MatchingReporter.h"

class Exp {
public:
	virtual bool evaluate(MatchingReporter* reporter = new MatchingReporter()) = 0;
};

class MatchExp : public Exp
{
public:
	MatchExp(Term* left, Term* right) : _left(left), _right(right) {}

	bool evaluate(MatchingReporter* reporter = new MatchingReporter()) override
	{
		auto tryWatch = [&](Term* term) {
			Variable* var = dynamic_cast<Variable*>(term);
			if (var)
			{
				reporter->watchVariable(var);
			}
		};

		bool result = _left->match(*_right);
		if (result)
		{
			tryWatch(_left);
			tryWatch(_right);
		}
		return result;
	}

private:
	Term* _left;
	Term* _right;
};

class ConjExp : public Exp
{
public:
	ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

	bool evaluate(MatchingReporter* reporter = new MatchingReporter()) override
	{
		auto doProcess = [&](Exp* exp) {
			bool result = exp->evaluate(reporter);
			if (!result)
			{
				reporter->clearPool();
			}
			return result;
		};
		return doProcess(_left) & doProcess(_right);
	}

private:
	Exp * _left;
	Exp * _right;
};

class DisjExp : public Exp
{
public:
	DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

	bool evaluate(MatchingReporter* reporter = new MatchingReporter()) override
	{
		auto doProcess = [&](Exp* exp) {
			bool result = exp->evaluate(reporter);
			if (result)
			{
				reporter->nextLayer();
			}
			else
			{
				reporter->clearPool();
			}
			return result;
		};
		return doProcess(_left) | doProcess(_right);
	}
private:
	Exp * _left;
	Exp * _right;
};

class BoolExp : public Exp
{
public:
	BoolExp(bool value) :_value(value) {}
	bool evaluate(MatchingReporter* reporter = new MatchingReporter()) override
	{
		return _value;
	}
private:
	bool _value;
};