#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Implicit
{
private:
	Implicit *left;
	Implicit *right;
	int key;
	int prior;
	int cnt;

	void upd_cnt() {
		cnt = 1;
		if (left != nullptr)
		{
			cnt += left->cnt;
		}
		if (right != nullptr)
		{
			cnt += right->cnt;
		}
	}

	Implicit* Merge(Implicit*);

	pair<Implicit*, Implicit*> Split(int);

	Implicit* Add(int);
public:
	Implicit(int k = 0) : key(k), prior(rand() % 100), left(nullptr), right(nullptr), cnt(1) {}
	Implicit(int k, int p) : key(k), prior(p), left(nullptr), right(nullptr), cnt(1) {}
	Implicit(int k, int p, Implicit* l, Implicit* r) : key(k), prior(p), left(l), right(r) {
		upd_cnt();
	}

	~Implicit();
};

