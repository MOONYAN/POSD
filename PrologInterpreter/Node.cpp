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
	return false;
}
