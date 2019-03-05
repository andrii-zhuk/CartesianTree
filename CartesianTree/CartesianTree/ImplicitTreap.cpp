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
		Implicit * t2 = new Implicit(key, prior, left, right);
		key = B->key; prior = y2; left = t2->Merge(B->left); right = B->right;
		upd_cnt();
		return this;
	}
}




Implicit::~Implicit()
{
	left->~Implicit();
	right->~Implicit();
	delete left;
	delete right;
}
