#pragma once
#include "Term.h"

class Proxy
{
private:
	string _proxyValue;
	Term* _proxyTerm = NULL;
	Proxy* _next = NULL;
public:
	Proxy(string proxyValue);
	~Proxy();
	string value();
};

