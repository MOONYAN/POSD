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
	Term* selfTerm = self->proxyTerm();
	Term* otherTerm = other->proxyTerm();
	return selfTerm->match(*other);
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
	if (this->value() != other.value())
	{
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
	}	
	return result;
}

bool Variable::assignable()
{
	_proxy = this->proxy();
	bool result = (_proxy == NULL);
	if (!result)
	{
		result = _proxy->assignable();
	}
	return result;
}

Proxy * Variable::proxy()
{
	if (_proxy != NULL)
	{
		_proxy = _proxy->getTailProxy();
	}
	return _proxy;
}

void Variable::setProxy(Proxy * node)
{
	_proxy = this->proxy();
	if (_proxy == NULL)
		_proxy = node;
	else
		_proxy->setTailProxy(node);
}

Term * Variable::proxyTerm()
{
	Term * result = NULL;
	_proxy = this->proxy();
	if (_proxy != NULL)
	{
		result = _proxy->getProxyTerm();
	}
	return result;
}

string Variable::symbol()
{
	return _symbol;
}

string Variable::value()
{
	_proxy = this->proxy();
	if (_proxy == NULL)
		return this->symbol();
	else
		return _proxy->value();
}

bool Variable::match(Term& other)
{
	bool result = true;
	if (this->value() != other.value())
	{
		if (assignable())
		{
			Proxy* node = new Proxy(&other);
			this->setProxy(node);
		}
		else
		{
			Term* proxyTerm = this->proxyTerm();
			result = proxyTerm->match(other);
		}
	}	
	return result;
}

bool Variable::tryAssign(Term& other)
{
	return this->match(other);
}
