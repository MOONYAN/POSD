#include "Proxy.h"

Proxy::Proxy(string dirtyValue) :_dirtyValue(dirtyValue)
{
}

Proxy::Proxy(Term * proxyTerm) : _proxyTerm(proxyTerm)
{
}

Proxy::~Proxy()
{
}

void Proxy::setDirtyValue(string dirtyValue)
{
	if (_next == NULL)
		_dirtyValue = dirtyValue;
	else
		_next->setDirtyValue(dirtyValue);
}

bool Proxy::assignable()
{
	if (_proxyTerm != NULL)
		return false;
	else if (_next == NULL)
		return true;
	else
		return _next->assignable();
}

Proxy * Proxy::getTailProxy()
{
	if (_next == NULL)
		return this;
	else
		return _next->getTailProxy();
}

void Proxy::setTailProxy(Proxy * node)
{
	if (_next == NULL)
		_next = node;
	else
		_next->setTailProxy(node);
}

Term * Proxy::getProxyTerm()
{
	if (_next != NULL)
		return _next->getProxyTerm();
	else
		return _proxyTerm;
}

string Proxy::value()
{
	if (_proxyTerm != NULL)
		return _proxyTerm->value();
	else if (_next != NULL)
		return _next->value();
	else
		return _dirtyValue;
}
