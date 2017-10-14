#include "Proxy.h"

Proxy::Proxy(string proxyValue) :_proxyValue(proxyValue)
{
}

Proxy::~Proxy()
{
}

string Proxy::value()
{
	return _proxyValue;
}
