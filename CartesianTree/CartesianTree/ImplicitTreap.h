#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Implicit
{
private:
	Implicit *left;
	Implicit *right;
	int min;
	int prior;
	int value;
	int cnt;
	int suma;

	void upd_cnt() {
		min = value;
		suma = value;
		cnt = 1;
		if (left != nullptr)
		{
			if (left->min < min)
				min = left->min;
			suma += left->suma;
			cnt += left->cnt;
		}
		if (right != nullptr)
		{
			if (right->min < min)
				min = right->min;
			suma += right->suma;
			cnt += right->cnt;
		}
	}

	Implicit* Merge(Implicit*);

	pair<Implicit*, Implicit*> Split(int, int);

public:
	Implicit(int v = 0) : value(value), prior(rand() % 100), left(nullptr), right(nullptr), cnt(1), suma(v), min(v) {}
	Implicit(int v, int p, Implicit* l = nullptr, Implicit* r = nullptr) : value(v), prior(p), left(l), right(r) {
		upd_cnt();
	}
	Implicit(int v, int p, Implicit* l, Implicit* r, int c, int s, int m) : value(v), prior(p), left(l), right(r), cnt(c), suma(s), min(m) {}
	
	Implicit* Add(int, int);
	void print();
	int Min(int, int);
	int Suma(int, int);
	~Implicit();
};

