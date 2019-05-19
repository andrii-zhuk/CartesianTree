#include "ImplicitTreap.h"
int Implicit::randomizer()
{
	return distribution(generator);
}

Implicit::node::node()
{
	left = nullptr;
	right = nullptr;
	prior = 0;
	subtree = 0;
	value = 0;
}

Implicit::node::node(int _value, int _prior)
{
	left = nullptr;
	right = nullptr;
	prior = _prior;
	value = _value;
	subtree = 1;
}

Implicit::node::~node()
{
		
}

int Implicit::getSubtree(node* u)
{
	if (!u)
	{
		return 0;
	}
	return u->subtree;
}

void Implicit::update(node* u)
{
	if (u)
		u->subtree = 1 + getSubtree(u->left) + getSubtree(u->right);
}

Implicit::node* Implicit::merge(node * t1, node * t2)
{
	if (!t1)
	{
		update(t2);
		return t2;
	}
	if (!t2)
	{
		update(t1);
		return t1;
	}

	if (t1->prior > t2->prior)
	{
		t1->right = merge(t1->right, t2);
		update(t1);
		return t1;
	}
	else
	{
		t2->left = merge(t1, t2->left);
		update(t2);
		return t2;
	}
}

pair<Implicit::node*, Implicit::node*> Implicit::split(node* t, int splitKey)
{
	if (!t)
	{
		return make_pair(nullptr, nullptr);
	}
	int curKey = 0;
	if (t->left)
	{
		curKey += (t->left)->subtree;
	}
	if (curKey <= splitKey)
	{
		pair<node*, node*> splitted = split(t->right, splitKey - curKey);
		t->right = splitted.first;
		update(t);
		return make_pair(t, splitted.second);
	}
	else
	{
		pair<node*, node*> splitted = split(t->left, splitKey);
		t->left = splitted.second;
		update(t);
		return make_pair(splitted.first, t);
	}
}

void Implicit::ARBTraversal(node *u)
{
	if (!u)
		return;
	ARBTraversal(u->left);
	cout << u->value << ' ';
	ARBTraversal(u->right);
}

void Implicit::clear(node* u) {
	if (!u)
	{
		return;
	}
	clear(u->left);
	clear(u->right);
	delete u;
}

int Implicit::dfs(node* u)
{
	if (!u)
	{
		return 0;
	}
	return max(dfs(u->left), dfs(u->right)) + 1;
}

Implicit::Implicit()
{
	generator = default_random_engine(chrono::high_resolution_clock::now().time_since_epoch().count());
	distribution = uniform_int_distribution<int>(0, 100000);
	root = nullptr;
}

Implicit::Implicit(int _value)
{
	generator = default_random_engine(chrono::high_resolution_clock::now().time_since_epoch().count());
	distribution = uniform_int_distribution<int>(0, 100000);
	root = new node(_value, randomizer());
}

void Implicit::push_back(int _value)
{
	root = merge(root, new node(_value, randomizer()));
}

void Implicit::insertAt(int _value, int _pos)
{
	pair<node*, node*> splitted = split(root, _pos - 1);
	splitted.first = merge(splitted.first, new node(_value, randomizer()));
	root = merge(splitted.first, splitted.second);
}

void Implicit::print()
{
	ARBTraversal(root);
}

int Implicit::getHeight()
{
	return dfs(root);
}

void Implicit::cleen()
{
	clear(root);
}

Implicit::~Implicit() {
	clear(root);
}