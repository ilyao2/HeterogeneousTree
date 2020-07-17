#include "HeterogeneousTree.h"

HeterogeneousTree::HeterogeneousTree()
{
	size = 0;
	root = nullptr;
}

HeterogeneousTree::HeterogeneousTree(const HeterogeneousTree&)
{
	// TODO: copyAll
}

HeterogeneousTree::~HeterogeneousTree()
{
	clear();
}

void HeterogeneousTree::append(int val, unsigned int childCount)
{
	append<int>(val, childCount);
}

void HeterogeneousTree::append(double val, unsigned int childCount)
{
	append<double>(val, childCount);
}

void HeterogeneousTree::append(std::string val, unsigned int childCount)
{
	append<std::string>(val, childCount);
}

void HeterogeneousTree::clear()
{
	delete root;
	size = 0;
	root = nullptr;
}
