#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Implicit
{
private:
	Implicit *left;
	Implicit *right;
	int prior;
	int value;
	int cnt;
	int suma;

	void upd_cnt() {
		suma = value;
		cnt = 1;
		if (left != nullptr)
		{
			suma += left->suma;
			cnt += left->cnt;
		}
		if (right != nullptr)
		{
			suma += right->suma;
			cnt += right->cnt;
		}
	}

	Implicit* Merge(Implicit*);

	pair<Implicit*, Implicit*> Split(int, int);

public:
	Implicit(int v = 0) : value(value), prior(rand() % 100), left(nullptr), right(nullptr), cnt(1) {}
	Implicit(int v, int p) : value(v), prior(p), left(nullptr), right(nullptr), cnt(1), suma(v) {}
	Implicit(int v, int p, Implicit* l, Implicit* r) : value(v), prior(p), left(l), right(r) {
		upd_cnt();
	}
	Implicit(int v, int p, Implicit* l, Implicit* r, int c, int s) : value(v), prior(p), left(l), right(r), cnt(c), suma(s) {}
	
	Implicit* Add(int, int);
	void print();

	int Suma(int, int);
	~Implicit();
};

