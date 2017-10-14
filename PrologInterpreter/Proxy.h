#pragma once
#include "Term.h"

class Proxy
{
private:
	Term* _proxyTerm = NULL;
	Proxy* _next = NULL;
public:
	Proxy();
	~Proxy();
};

