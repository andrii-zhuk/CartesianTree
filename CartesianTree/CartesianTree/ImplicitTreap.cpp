#include "ImplicitTreap.h"


Implicit* Implicit::Merge(Implicit* B)
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
		upd_cnt();
		return this;
	}
	else
	{
		Implicit * t2 = new Implicit(value, prior, left, right);
		value = B->value; prior = y2; left = t2->Merge(B->left); right = B->right;
		upd_cnt();
		return this;
	}
}


pair<Implicit*, Implicit*> Implicit::Split(int val, int add = 0)
{
	int curKey = add;
	if (left != nullptr)
	{
		curKey += left->cnt;
	}
	if (curKey <= val)
	{
		if (right == nullptr)
		{
			upd_cnt();
			return make_pair(this, right);
		}
		add += 1;
		if (left != nullptr)
		{
			add += left->cnt;
		}
		pair<Implicit*, Implicit*> cur = right->Split(val, add);
		upd_cnt();
		return make_pair(new Implicit(value, prior, left, cur.first), cur.second);
	}
	else
	{
		if (left == nullptr)
		{
			upd_cnt();
			return make_pair(left, this);
		}
		pair<Implicit*, Implicit*> cur = left->Split(val, add);
		return make_pair(cur.first, new Implicit(value, prior, cur.second, right));
	}
}


Implicit* Implicit::Add(int v, int pos)
{
	int y = rand() % 100; // add random generator
	Implicit * t2 = new Implicit(*this);
	pair<Implicit*, Implicit*> cur = t2->Split(pos-1);
	Implicit* toAdd = new Implicit(v, y);
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
	value = cur.first->value; prior = cur.first->prior; left = cur.first->left; right = cur.first->right;
	upd_cnt();
	return this;
}

void Implicit::print()
{
	if (left != nullptr)
	{
		left->print();
	}
	cout << value << " + " << prior << endl;
	if (right != nullptr)
	{
		right->print();
	}
}

int Implicit::Suma(int l, int r)
{
	if (l < 1)
		l = 1;
	if (r > cnt)
		r = cnt;
	pair<Implicit*, Implicit*> cur = Split(l - 1);
	pair<Implicit*, Implicit*> cur2 = cur.second->Split(r-l);
	int ret = 0;
	if (cur2.first != nullptr)
		ret += cur2.first->suma;
	cur.first->Merge(cur2.first->Merge(cur2.second));

	return ret;
}

int Implicit::Min(int l, int r)
{
	if (l < 1)
		l = 1;
	if (r > cnt)
		r = cnt;
	pair<Implicit*, Implicit*> cur = Split(l - 1);
	pair<Implicit*, Implicit*> cur2 = cur.second->Split(r - l);
	int ret = 0;
	if (cur2.first != nullptr)
		ret += cur2.first->min;
	cur.first->Merge(cur2.first->Merge(cur2.second));

	return ret;
}

Implicit::~Implicit()
{
	if (left != nullptr)
	{
		left->~Implicit();
	}
	if (right != nullptr)
	{
		right->~Implicit();
	}
}
