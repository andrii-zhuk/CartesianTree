#pragma once
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

class ImplicitTreapOnArray
{
private:
	default_random_engine generator;
	uniform_int_distribution<int> distribution;
	int randomizer();
	struct node {
		int left;
		int right;
		int prior;
		int subtree;
		int value;
		int parent;
		node();
		node(int _value, int _prior);
		node(int _value, int _parent, int _prior);
	};
	node treap[1000];
	int size;
	int root;

	int getSubtree(int u);
	void update(int u);
	int merge(int t1, int t2);
	pair<int, int> split(int t, int splitKey);
	
	void ARBTraversal(int u);
	void remove(int u);
public:
	ImplicitTreapOnArray();
	ImplicitTreapOnArray(int _value);
	void push_back(int _value);
	void insertAt(int _value, int _pos);
	void print();
	void print2()
	{
		for (int i = 0; i < 100; ++i)
		{
			cout << treap[i].left << ' ' << treap[i].parent << ' ' << treap[i].prior << '\n';

		}
	}
	void clear()
	{
		remove(root);
	}
	~ImplicitTreapOnArray();
};

