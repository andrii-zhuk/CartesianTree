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

	void Split(int, Treap *&, Treap *&);

	Treap* Add(int);

	int randomize();
public:
	Treap(int k = 0) : key(k), prior(randomize()), left(nullptr), right(nullptr) {}
	Treap(int k, int p) : key(k), prior(p), left(nullptr), right(nullptr) {}
	Treap(int k, int p, Treap* l, Treap* r) : key(k), prior(p), left(l), right(r) {}
	
	bool Find(int);

	Treap* Insert(int);

	void print();

	~Treap();
};

