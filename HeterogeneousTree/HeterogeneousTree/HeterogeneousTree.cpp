#include "HeterogeneousTree.h"

HeterogeneousTree::HeterogeneousTree()
{
	size = 0;
	root = nullptr;
}

HeterogeneousTree::HeterogeneousTree(const HeterogeneousTree& obj)
{
	clear();
	std::queue<BaseNode*> q;
	q.push(obj.root);
	BaseNode* temp;
	while (!q.empty())
	{

		temp = q.front();
		for (unsigned int j = 0; j < temp->childCount; j++)
			q.push(temp->childs[j]);

		if (temp->getType() == typeid(std::string))
		{
			Node<std::string>* node = dynamic_cast<Node<std::string>*>(temp);
			append(node->val, node->maxChildCount);
		}
		else if (temp->getType() == typeid(int))
		{
			Node<int>* node = dynamic_cast<Node<int>*>(temp);
			append(node->val, node->maxChildCount);
		}
		else if (temp->getType() == typeid(double))
		{
			Node<double>* node = dynamic_cast<Node<double>*>(temp);
			append(node->val, node->maxChildCount);
		}
		else
		{
			throw std::exception("Unknowing type");
		}
		q.pop();
	}
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

int HeterogeneousTree::getSize()
{
	return size;
}

bool HeterogeneousTree::isEmpty()
{
	return (size == 0) ? true : false;
}

void HeterogeneousTree::clear()
{
	delete root;
	size = 0;
	root = nullptr;
}

unsigned int HeterogeneousTree::getNodeLevel(unsigned int index)
{
	if (index >= size)
		throw std::out_of_range("Out of range, check size!");
	std::queue<BaseNode*> q;
	int i = 0;
	q.push(root);
	BaseNode* temp;
	temp = q.front();
	while (i != index)
	{
		for (unsigned int j = 0; j < temp->maxChildCount; j++)
			q.push(temp->childs[j]);
		q.pop();
		i++;
		temp = q.front();
	}
	return temp->level;
}

unsigned int HeterogeneousTree::getNodeChildCount(unsigned int index)
{
	if (index >= size)
		throw std::out_of_range("Out of range, check size!");
	std::queue<BaseNode*> q;
	int i = 0;
	q.push(root);
	BaseNode* temp;
	temp = q.front();
	while (i != index)
	{
		for (unsigned int j = 0; j < temp->maxChildCount; j++)
			q.push(temp->childs[j]);
		q.pop();
		i++;
		temp = q.front();
	}
	return temp->childCount;
}
