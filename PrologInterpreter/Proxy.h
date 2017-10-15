#pragma once
#include "Term.h"

class Proxy
{
private:
	string _dirtyValue;
	Term* _proxyTerm = NULL;
	Proxy* _next = NULL;
public:
	Proxy(string dirtyValue);
	~Proxy();
	void setDirtyValue(string dirtyValue);
	string value();
};

