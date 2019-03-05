#include <iostream>
#include "Treap.h"
#include "ImplicitTreap.h"
#include <ctime>
using namespace std;

struct item {
	int key, prior;
	item * l, *r;
	item() { }
	item(int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};
typedef item * pitem;

void split(pitem t, int key, pitem & l, pitem & r) {
	if (!t)
		l = r = NULL;
	else if (key < t->key)
		split(t->l, key, l, t->l), r = t;
	else
		split(t->r, key, t->r, r), l = t;
}

void insert(pitem & t, pitem it) {
	if (!t)
		t = it;
	else if (it->prior > t->prior)
		split(t, it->key, it->l, it->r), t = it;
	else
		insert(it->key < t->key ? t->l : t->r, it);
}

void merge(pitem & t, pitem l, pitem r) {
	if (!l || !r)
		t = l ? l : r;
	else if (l->prior > r->prior)
		merge(l->r, l->r, r), t = l;
	else
		merge(r->l, l, r->l), t = r;
}

void erase(pitem & t, int key) {
	if (t->key == key)
		merge(t, t->l, t->r);
	else
		erase(key < t->key ? t->l : t->r, key);
}

pitem unite(pitem l, pitem r) {
	if (!l || !r)  return l ? l : r;
	if (l->prior < r->prior)  swap(l, r);
	pitem lt, rt;
	split(r, l->key, lt, rt);
	l->l = unite(l->l, lt);
	l->r = unite(l->r, rt);
	return l;
}

int main()
{
	std::cout << "hi, cursova!" << endl;
	
	Treap T(0, 0);
	auto t = clock();
	for (int i = 0; i < 100000; i++)
	{
		T.Insert(i+1);
	}
	cout << double(clock() - t) / CLOCKS_PER_SEC << endl;
	//T.Insert(100005);
	//T.print();

	t = clock();
	pitem cur = new item(0, rand() % 1000000);
	for (int i = 1; i < 100000; ++i)
	{
		insert(cur, new item(i, rand() % 1000000));
	}

	cout << double(clock() - t) / CLOCKS_PER_SEC << endl;


	system("pause");
	return 0;
}