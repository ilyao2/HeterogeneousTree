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

void HeterogeneousTree::serialize(std::string path)
{
	if (isEmpty())
		throw std::exception("Tree is empty!");
	std::ofstream out;          
	out.open(path, std::ios::binary); 
	if (out.is_open())
	{
		out.write((char*)&size, sizeof(size));

		std::queue<BaseNode*> q;
		q.push(root);
		BaseNode* temp;
		while (!q.empty())
		{

			temp = q.front();
			for (unsigned int j = 0; j < temp->childCount; j++)
				q.push(temp->childs[j]);

			if (temp->getType() == typeid(std::string))
			{
				Node<std::string>* node = dynamic_cast<Node<std::string>*>(temp);
				std::string typeName = typeid(std::string).name();
				int typeNameSize = typeName.length()+1;
				out.write((char*)&typeNameSize, sizeof(typeNameSize));
				out.write((char*)(typeName.c_str()), typeNameSize);
				out.write((char*)&node->maxChildCount, sizeof(node->maxChildCount));
				int nodeStringSize = node->val.length() + 1;
				out.write((char*)&nodeStringSize, sizeof(nodeStringSize));
				out.write((char*)node->val.c_str(), nodeStringSize);
			}
			else if (temp->getType() == typeid(int))
			{
				Node<int>* node = dynamic_cast<Node<int>*>(temp);
				std::string typeName = typeid(int).name();
				int typeNameSize = typeName.length() + 1;
				out.write((char*)&typeNameSize, sizeof(typeNameSize));
				out.write((char*)(typeName.c_str()), typeNameSize);
				out.write((char*)&node->maxChildCount, sizeof(node->maxChildCount));
				out.write((char*)&node->val, sizeof(node->val));
			}
			else if (temp->getType() == typeid(double))
			{
				Node<double>* node = dynamic_cast<Node<double>*>(temp);
				std::string typeName = typeid(double).name();
				int typeNameSize = typeName.length() + 1;
				out.write((char*)&typeNameSize, sizeof(typeNameSize));
				out.write((char*)(typeName.c_str()), typeNameSize);
				out.write((char*)&node->maxChildCount, sizeof(node->maxChildCount));
				out.write((char*)&node->val, sizeof(node->val));
			}
			else
			{
				throw std::exception("Unknowing type");
			}
			q.pop();
		}
		out.close();
	}
	else
	{
		throw std::exception("Can't open file");
	}
	
}

void HeterogeneousTree::deserialize(std::string path)
{
	std::ifstream in;
	in.open(path, std::ios::binary);
	if (in.is_open())
	{
		clear();
		int treeSize;
		in.read((char*)&treeSize, sizeof(treeSize));
		for (int i = 0; i < treeSize; i++)
		{
			int typeNameSize;
			in.read((char*)&typeNameSize, sizeof(typeNameSize));
			char* typeNameBuf = new char[typeNameSize];
			in.read(typeNameBuf, typeNameSize);
			int childCount;
			in.read((char*)&childCount, sizeof(childCount));

			if (std::strcmp(typeNameBuf, typeid(std::string).name()) == 0)
			{
				int nodeStringSize;
				in.read((char*)&nodeStringSize, sizeof(nodeStringSize));
				char* nodeValBuf = new char[nodeStringSize];
				in.read(nodeValBuf, nodeStringSize);
				std::string nodeString = nodeValBuf;
				append(nodeString, childCount);
				delete[] nodeValBuf;
			}
			else if (std::strcmp(typeNameBuf, typeid(int).name()) == 0)
			{
				int val;
				in.read((char*)&val, sizeof(val));
				append(val, childCount);
			}
			else if (std::strcmp(typeNameBuf, typeid(double).name()) == 0)
			{
				double val;
				in.read((char*)&val, sizeof(val));
				append(val, childCount);
			}
			else
			{
				throw std::exception("Unknowing type");
			}

			delete[] typeNameBuf;
		}
		in.close();
	}
	else
	{
		throw std::exception("Can't open file");
	}
}
