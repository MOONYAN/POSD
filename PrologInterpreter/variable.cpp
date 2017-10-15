#include "Variable.h"

//set new node and assign to both
void createNewNode(Variable* self, Variable* other)
{
	string dirtyValue = other->value();
	Proxy* node = new Proxy(dirtyValue);
	self->setProxy(node);
	other->setProxy(node);
}

void copyNodeToSelf(Variable* self, Variable* other)
{
	Proxy* node = other->proxy();
	self->setProxy(node);
}

void copyNodeToOther(Variable* self, Variable* other)
{
	Proxy* node = self->proxy();
	node->setDirtyValue(other->value());
	other->setProxy(node);
}

bool doMatchTerm(Variable* self, Variable* other)
{
	Term* selfTerm = self->proxyTem();
	Term* otherTerm = other->proxyTem();
	return selfTerm->match(*other);
}

bool Variable::canAssign()
{
	return _proxyTerm == this;
}

Variable::Variable(string symbol)
{
	_symbol = symbol;
}

Variable::~Variable()
{
}

bool Variable::match(Variable & other)
{
	bool result = true;
	if (this->assignable())
	{
		if (other.assignable())
		{
			createNewNode(this, &other);
		}
		else
		{
			copyNodeToSelf(this, &other);
		}
	}
	else
	{
		if (other.assignable())
		{
			copyNodeToOther(this, &other);
		}
		else
		{
			result = doMatchTerm(this, &other);
		}
	}
	return result;
}

bool Variable::assignable()
{
	return false;
}

Proxy * Variable::proxy()
{
	return _proxy;
}

void Variable::setProxy(Proxy * node)
{
}

Term * Variable::proxyTem()
{
	return nullptr;
}

string Variable::symbol()
{
	return _symbol;
}

string Variable::value()
{
	string result = this->_symbol;
	if (!canAssign())
	{
		result = _proxyTerm->value();
	}
	return result;
}

bool Variable::match(Term& other)
{
	bool result = true;
	if (canAssign())
	{
		_proxyTerm = &other;
	}
	else
	{
		result = this->value() == other.value();
	}
	return result;
}

bool Variable::tryAssign(Term& other)
{
	bool result = (canAssign());
	if (result)
	{
		_proxyTerm = &other;
	}
	return result;
}
