#pragma once
#include "Iterator.h"
#include "Term.h"
#include <vector>

class DFSIterator : public Iterator<Term*>
{
public:
	DFSIterator(Term* term) :_root(term) 
	{

	}

	// Inherited via Iterator
	virtual void first() override
	{
		_index = 0;
		_terms.clear();
		dfs(_root);
	}
	virtual void next() override
	{
		_index++;
	}
	virtual Term* currentItem() const override
	{
		return _terms[_index];
	}
	virtual bool isDone() const override
	{
		return _index >= (int)_terms.size();
	}

	void dfs(Term* root)
	{
		Iterator<Term*> *it = root->createIterator();
		for (it->first(); !it->isDone(); it->next())
		{
			Term* child = it->currentItem();
			_terms.push_back(child);
			dfs(child);
		}
	}

private:
	int _index = 0;
	Term* _root;
	vector<Term*> _terms;
};