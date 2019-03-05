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

void Treap::Split(int val, Treap *& l, Treap *& r)
{
	if (key <= val)
	{
		if (right == nullptr)
		{
			l = this;
			r = right;
			return;
		}
		right->Split(val, right, r);
		l = this;
	}
	else
	{
		if (left == nullptr)
		{
			l = left;
			r = this;
			return;
		}
		left->Split(val, l, left);
		r = this;
	}
}

Treap* Treap::Add(int val)
{
	int y = randomize(); // add random generator
	Treap * t2 = new Treap(key, prior, left, right);
	pair<Treap*, Treap*> cur;
	t2->Split(val, cur.first, cur.second);
	Treap* toAdd = new Treap(val, y);
	toAdd->Merge(cur.second);
	if (cur.first == nullptr)
	{
		cur.first = toAdd;
	}
	else
	{
		cur.first->Merge(toAdd);
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

int Treap::randomize()
{
	return rand() % 1000 * 1000000 + rand() % 1000*1000 + rand() % 1000;
}

Treap::~Treap()
{
	if (left != nullptr)
		left->~Treap();
	if (right != nullptr)
		right->~Treap();
}