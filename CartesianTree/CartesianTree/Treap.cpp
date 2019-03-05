#include "Treap.h"

Treap* Treap::Merge(Treap* B)
{
	if (B == nullptr)
	{
		return this;
	}
	int y1, y2;
	y1 = prior;
	y2 = B->prior;
	if (y1 > y2)
	{
		if (right == nullptr)
		{
			right = B;
		}
		else
		{
			right = right->Merge(B);
		}
		return this;
	}
	else
	{
		Treap * t2 = new Treap(key, prior, left, right);
		key = B->key; prior = y2; left = t2->Merge(B->left); right = B->right;
		return this;
	}
}

pair<Treap*, Treap*> Treap::Split(int val)
{
	if (key <= val)
	{
		if (right == nullptr)
		{
			return make_pair(this, right);
		}
		pair<Treap*, Treap*> cur = right->Split(val);
		return make_pair(new Treap(key, prior, left, cur.first), cur.second);
	}
	else
	{
		if (left == nullptr)
		{
			return make_pair(left, this);
		}
		pair<Treap*, Treap*> cur = left->Split(val);
		return make_pair(cur.first, new Treap(key, prior, cur.second, right));
	}
}

Treap* Treap::Add(int val)
{
	int y = rand() % 100; // add random generator
	Treap * t2 = new Treap(key, prior, left, right);
	pair<Treap*, Treap*> cur = t2->Split(val);
	Treap* toAdd = new Treap(val, y);
	if (cur.first == nullptr)
	{
		cur.first = toAdd;
	}
	else
	{
		cur.first->Merge(toAdd);
	}
	if (cur.second != nullptr)
	{
		cur.first->Merge(cur.second);
	}
	key = cur.first->key; prior = cur.first->prior; left = cur.first->left; right = cur.first->right;
	return this;
}

bool Treap::Find(int val)
{
	if (key == val)
		return true;
	if (key < val)
	{
		if (left == nullptr)
			return false;
		return left->Find(val);
	}
	else
	{
		if (right == nullptr)
			return false;
		return right->Find(val);
	}
}

Treap* Treap::Insert(int val)
{
	if (this->Find(val))
	{
		return this;
	}
	return this->Add(val);
}

void Treap::print()
{
	if (left != nullptr)
	{
		cout << "leftSon" << endl;
		left->print();
	}
	cout << key << " + " << prior << endl;
	if (right != nullptr)
	{
		cout << "rightSon" << endl;
		right->print();
	}
}

Treap::~Treap()
{
	left->~Treap();
	right->~Treap();
	delete left;
	delete right;
}