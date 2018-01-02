#pragma once
#include "Term.h"

enum Operators { SEMICOLON, COMMA, EQUALITY, TERM };

class Node
{
public:
	Operators payload;
	Term* term;
	Node* left;
	Node* right;

	Node(Operators op) :payload(op), term(0), left(0), right(0) {}
	Node(Operators op, Term *t, Node *l, Node *r) :payload(op), term(t), left(l), right(r) {}
	~Node();
	bool evaluate();
};

