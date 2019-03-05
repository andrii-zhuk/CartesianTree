#pragma once
#include <vector>
#include <iostream>


using namespace std;
class Treap
{
private:
	Treap *left;
	Treap *right;
	int key;
	int prior;

	Treap* Merge(Treap*);

	pair<Treap*, Treap*> Split(int);

	Treap* Add(int);
public:
	Treap(int k = 0) : key(k), prior(rand()% 1000200), left(nullptr), right(nullptr) {}
	Treap(int k, int p) : key(k), prior(p), left(nullptr), right(nullptr) {}
	Treap(int k, int p, Treap* l, Treap* r) : key(k), prior(p), left(l), right(r) {}
	
	bool Find(int);

	Treap* Insert(int);

	void print();

	~Treap();
};

