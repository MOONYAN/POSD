#pragma once

#include "Term.h"

class Exp {
public:
	virtual bool evaluate() = 0;
};

class MatchExp : public Exp
{
public:
	MatchExp(Term* left, Term* right) : _left(left), _right(right) {}

	bool evaluate() override
	{
		return _left->match(*_right);
	}

private:
	Term* _left;
	Term* _right;
};

class ConjExp : public Exp
{
public:
	ConjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

	bool evaluate() override
	{
		return (_left->evaluate() && _right->evaluate());
	}

private:
	Exp * _left;
	Exp * _right;
};

class DisjExp : public Exp
{
public:
	DisjExp(Exp *left, Exp *right) : _left(left), _right(right) {}

	bool evaluate() override
	{
		return (_left->evaluate() || _right->evaluate());
	}

private:
	Exp * _left;
	Exp * _right;
};

class BoolExp : public Exp
{
public:
	BoolExp(bool value) :_value(value) {}
	bool evaluate() override
	{
		return _value;
	}
private:
	bool _value;
};