#pragma once
#include <stdexcept>
#include <typeinfo>
#include <sstream>
#include <fstream>
#include <string>
#include <queue>


class HeterogeneousTree
{
private:

	//������� ����, ��� ����������� �������� ��� ������ �����
	class BaseNode
	{
	public:
		unsigned int maxChildCount;
		unsigned int childCount = 0;
		unsigned int level = 0;
		BaseNode** childs;
		BaseNode(unsigned int ChildCount = 2, unsigned int Level = 0)
		{
			maxChildCount = ChildCount;
			level = Level;
			childs = new BaseNode * [maxChildCount];
			for (unsigned int i = 0; i < maxChildCount; i++)
				childs[i] = nullptr;
		}

		~BaseNode()
		{
			for (unsigned int i = 0; i < maxChildCount; i++)
				if (childs[i] != nullptr)
				{
					delete childs[i];
					childs[i] = nullptr;
				}
			delete[] childs;
			childs = nullptr;
		}

		bool isFull()
		{
			return (childCount == maxChildCount) ? true : false;
		}

		virtual const type_info& getType() = 0;

	};


	template <class T>
	class Node : public BaseNode
	{
	public:
		T val;
		Node(T val, unsigned int ChildCount, unsigned int level = 0) : BaseNode(ChildCount, level)
		{
			this->val = val;
		}
		~Node() {};

		const type_info& getType()
		{
			return typeid(T);
		}

	};


	int size;
	BaseNode* root;

	template <class T>
	void append(T val, unsigned int childCount);
public:
	HeterogeneousTree();
	HeterogeneousTree(const HeterogeneousTree&);
	~HeterogeneousTree();

	//��� ���������� ������ ����� ���������, ������� �������� ����� ���� � ����,
	//�.�. ������� �� �� �����, �� ���, �� �������, �� ���-�� ��������
	//����������� ������ ����� �� ������ � ������
	//����� �������, ����� ����� �������� ���� �������, �� ����� �����, ������� ��� ����� �� ���������
	void append(int val, unsigned int childCount);
	void append(double val, unsigned int childCount);
	void append(std::string val, unsigned int childCount);

	int getSize();
	bool isEmpty();
	//TODO: �������� �������� ��� �������������
	//void cut(unsigned int index);
	void clear();
	unsigned int getNodeLevel(unsigned int index);
	unsigned int getNodeChildCount(unsigned int index);

	//�������� ������� � ���� ������������ ���������� � ���������� ���
	//� ���������� � ������ ����(���,���-�� ��������, ��������)
	void serialize(std::string path);
	void deserialize(std::string path);

	//��������� ����� ��������� ������ ������� ����
	//������ ����� ����������� ������������ �����
	//� ������ ������� ���� ��������
	//��� ���������� ���-�� �����, ������� ����� ������� ������,
	//����� ����� �������� ����� �������� �� ������������ ����
	template<class T>
	T getValue(unsigned int index);

	//������������� ��� ������, ����� �� ��� ������� ���������, ��� ����������� ������
	//� ���� �� ��� �� ���������� ���
	template<>
	std::string getValue<std::string>(unsigned int index);
};

template<class T>
void HeterogeneousTree::append(T val, unsigned int childCount)
{
	if (size == 0)
	{
		root = new Node<T>(val, childCount);
		size++;
		return;
	}
	std::queue<BaseNode*> q;
	q.push(root);
	while (!q.empty())
	{
		BaseNode* temp = q.front();
		if (temp->isFull())
		{
			for (unsigned int i = 0; i < temp->maxChildCount; i++)
				q.push(temp->childs[i]);
			q.pop();
		}
		else
		{
			temp->childs[temp->childCount] = new Node<T>(val, childCount, temp->level + 1);
			temp->childCount++;
			size++;
			return;
		}
	}
	throw std::overflow_error("Tree overflow!");
}

template<class T>
T HeterogeneousTree::getValue(unsigned int index)
{
	if (index >= size)
		throw std::out_of_range("Out of range, check size!");
	//��� ������ � ������ ����� ������������ ������� � ���� ��������.
	//��� ������������� ����� ��������� ������� �� ��������
	//���� ������ ������ ��������� ��� ����������� � ������ �������
	std::queue<BaseNode*> q;
	int i = 0;
	q.push(root);
	BaseNode* temp;
	temp = q.front();
	while (i != index)
	{
		for (int j = 0; j < temp->maxChildCount; j++)
			q.push(temp->childs[j]);
		q.pop();
		i++;
		temp = q.front();
	}

	if (temp->getType() == typeid(std::string))
	{
		Node<std::string>* node = dynamic_cast<Node<std::string>*>(temp);

		return static_cast<T>(std::atof(node->val.c_str()));
	}
	else if (temp->getType() == typeid(int))
	{
		Node<int>* node = dynamic_cast<Node<int>*>(temp);
		return static_cast<T>(node->val);
	}
	else if (temp->getType() == typeid(double))
	{
		Node<double>* node = dynamic_cast<Node<double>*>(temp);
		return static_cast<T>(node->val);
	}
	else
	{
		throw std::exception("Unknowing type");
	}
}

template <>
std::string HeterogeneousTree::getValue<std::string>(unsigned int index)
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

	if (temp->getType() == typeid(std::string))
	{
		Node<std::string>* node = dynamic_cast<Node<std::string>*>(temp);
		return node->val;
	}
	else if (temp->getType() == typeid(int))
	{
		Node<int>* node = dynamic_cast<Node<int>*>(temp);
		std::ostringstream os;
		os << node->val;

		std::string s = os.str();
		return s;
	}
	else if (temp->getType() == typeid(double))
	{
		Node<double>* node = dynamic_cast<Node<double>*>(temp);
		std::ostringstream os;
		os << node->val;
		std::string s = os.str();
		return s;
	}
	else
	{
		throw std::exception("Unknowing type");
	}
}
