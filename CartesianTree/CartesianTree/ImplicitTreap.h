#pragma once
using namespace std;
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

class Implicit
{
private:
	default_random_engine generator;
	uniform_int_distribution<int> distribution;
	int randomizer();
	struct node {
		node* left;
		node* right;
		int prior;
		int subtree;
		int value;
		node();
		node(int _value, int _prior);
		~node();
	};
	int getSubtree(node* u);
	void update(node* u);
	node* merge(node * t1, node * t2);
	pair<node*, node*> split(node* t, int splitKey);

	void ARBTraversal(node *u);
	int dfs(node* u);
	void clear(node* u);

	node* root;
public:
	Implicit();
	Implicit(int _value);
	void push_back(int _value);
	void insertAt(int _value, int _pos);
	void print();
	int getHeight();
	void cleen();
	~Implicit();
};

