#include "ImplicitTreapOnArray.h"

int ImplicitTreapOnArray::randomizer()
{
	return distribution(generator);
}

ImplicitTreapOnArray::node::node()
{
	left = -1;
	right = -1;
	prior = 0;
	value = 0;
	subtree = 1;
	parent = -1;
}

ImplicitTreapOnArray::node::node(int _value, int _prior)
{
	left = -1;
	right = -1;
	prior = _prior;
	value = _value;
	subtree = 1;
	parent = -1;
}

ImplicitTreapOnArray::node::node(int _value, int _parent, int _prior)
{
	left = -1;
	right = -1;
	prior = _prior;
	value = _value;
	subtree = 1;
	parent = _parent;
}

int ImplicitTreapOnArray::getSubtree(int u)
{
	if (u == -1)
		return 0;
	return treap[u].subtree;
}

void ImplicitTreapOnArray::update(int u)
{
	if (u != -1)
		treap[u].subtree = 1 + getSubtree(treap[u].left) + getSubtree(treap[u].left);
}

int ImplicitTreapOnArray::merge(int t1, int t2)
{
	if (t1 == -1)
	{
		return t2;
	}
	if (t2 == -1)
	{
		return t1;
	}
	int res;
	if (treap[t1].prior > treap[t2].prior)
	{
		if (treap[t1].right != -1)
		{
			treap[treap[t1].right].parent = -1;
		}
		res = merge(treap[t1].right, t2);
		if (res != -1)
		{
			treap[res].parent = t1;
		}
		treap[t1].right = res;
		update(t1);
		return t1;
	}
	else
	{
		if (treap[t2].left != -1)
		{
			treap[treap[t2].left].parent = -1;
		}
		res = merge(t1, treap[t2].left);
		if (res != -1)
		{
			treap[res].parent = t2;
		}
		treap[t2].left = res;
		update(t2);
		return t2;
	}
}

pair<int, int> ImplicitTreapOnArray::split(int t, int splitKey)
{
	if (t == -1)
	{
		return make_pair(-1, -1);
	}
	int curKey = 0;
	if (treap[t].left != -1)
	{
		curKey += treap[treap[t].left].subtree;
	}
	if (curKey <= splitKey)
	{
		pair<int, int> splitted = split(treap[t].right, splitKey - curKey);
		treap[t].right = splitted.first;
		if (treap[t].right != -1)
		{
			treap[treap[t].right].parent = t;
		}
		update(t);
		return make_pair(t, splitted.second);
	}
	else
	{
		pair<int, int> splitted = split(treap[t].left, splitKey);
		treap[t].left = splitted.second;
		if (treap[t].left != -1)
		{
			treap[treap[t].left].parent = t;
		}
		update(t);
		return make_pair(splitted.first, t);
	}
}

void ImplicitTreapOnArray::ARBTraversal(int u)
{
	if (u == -1)
		return;
	ARBTraversal(treap[u].left);
	cout << treap[u].value << ' ';
	ARBTraversal(treap[u].right);
}

void ImplicitTreapOnArray::remove(int u)
{
	if (u == -1)
		return;
	remove(treap[u].left);
	remove(treap[u].right);
	treap[u].left = treap[u].right = -1;
	int parent = treap[u].parent;
	if (treap[parent].left == u)
	{
		treap[parent].left = -1;
	}
	else
	{
		treap[parent].right = -1;
	}
	int end = size - 1;
	if (root == end)
	{
		root = u;
	}
	else
	{
		int parentEnd = treap[end].parent;
		if (treap[parentEnd].left == end)
		{
			treap[parentEnd].left = u;
		}
		else
		{
			treap[parentEnd].right = u;
		}
	}
	if (treap[end].left != -1)
		treap[treap[end].left].parent = u;
	if (treap[end].right != -1)
		treap[treap[end].right].parent = u;
	treap[u].parent = -1;
	swap(treap[u], treap[end]);
	size--;
}

ImplicitTreapOnArray::ImplicitTreapOnArray()
{
	root = -1;
	size = 0;
	generator = default_random_engine(chrono::high_resolution_clock::now().time_since_epoch().count());
	distribution = uniform_int_distribution<int>(0, 100000);
}

ImplicitTreapOnArray::ImplicitTreapOnArray(int _value)
{
	root = 0;
	size = 0;
	generator = default_random_engine(chrono::high_resolution_clock::now().time_since_epoch().count());
	distribution = uniform_int_distribution<int>(0, 100000);
	treap[size++] = (node(_value, randomizer()));
}

void ImplicitTreapOnArray::push_back(int _value)
{
	generator = default_random_engine(chrono::high_resolution_clock::now().time_since_epoch().count());
	distribution = uniform_int_distribution<int>(0, 100000);
	treap[size++] = (node(_value, randomizer()));
	root = merge(root, size - 1);
	if (root != -1)
	{
		treap[root].parent = -1;
	}
}

void ImplicitTreapOnArray::insertAt(int _value, int _pos)
{
	pair<int, int> splitted = split(root, _pos - 1);
	treap[size++] = (node(_value, randomizer()));
	splitted.first = merge(splitted.first, size - 1);
	root = merge(splitted.first, splitted.second);
}

void ImplicitTreapOnArray::print()
{
	ARBTraversal(root);
}

ImplicitTreapOnArray::~ImplicitTreapOnArray()
{
	remove(root);
	size = 0;
}