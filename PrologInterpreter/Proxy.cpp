#include "Proxy.h"

Proxy::Proxy(string dirtyValue) :_dirtyValue(dirtyValue)
{
}

Proxy::~Proxy()
{
}

void Proxy::setDirtyValue(string dirtyValue)
{	
}

string Proxy::value()
{
	return _dirtyValue;
}
