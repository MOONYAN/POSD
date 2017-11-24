#include "Node.h"

Node::~Node()
{
}

bool Node::evaluate()
{
	if (this->payload == EQUALITY)
	{
		Term* left = this->left->term;
		Term* right = this->right->term;
		return left->match(*right);
	}
	else if (this->payload == COMMA)
	{		
		return left->evaluate() & right->evaluate();
	}
	else if (this->payload == SEMICOLON)
	{
		return left->evaluate() | right->evaluate();
	}
	return false;
}
