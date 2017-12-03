#pragma once
#include "Iterator.h"
#include "Term.h"
#include <vector>
#include <queue>

class BFSIterator : public Iterator<Term*>
{
public:
	BFSIterator(Term* term) :_root(term)
	{

	}

	// Inherited via Iterator
	virtual void first() override
	{
		_index = 1;
		_terms.clear();
		bfs(_root);
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

	void bfs(Term* root)
	{
		queue<Term*> q;
		q.push(root);
		while (!q.empty())
		{			
			Term* term = q.front();
			q.pop();
			_terms.push_back(term);
			Iterator<Term*> *it = term->createIterator();
			for (it->first(); !it->isDone(); it->next())
			{
				Term* child = it->currentItem();
				q.push(child);
			}
		}
	}

private:
	int _index = 1;
	Term* _root;
	vector<Term*> _terms;
};