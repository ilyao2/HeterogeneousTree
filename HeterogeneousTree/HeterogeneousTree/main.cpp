#include <iostream>
#include "HeterogeneousTree.h"

using namespace std;

void showTree(HeterogeneousTree&);

int main()
{
	HeterogeneousTree tree;
	tree.append(8, 2);
	tree.append((std::string)("bar"), 3);
	tree.append((std::string)("baz"), 2);
	tree.append(2.015, 1);
	tree.append(2015, 0);
	tree.append((std::string)("2015"), 0);
	tree.append((std::string)("foo"), 0);
	tree.append(6.28318, 1);
	tree.append(9, 0);
	tree.append((std::string)("hello"), 0);

	tree.serialize("output.txt");
	HeterogeneousTree tree2;
	tree2.deserialize("output.txt");
	showTree(tree2);


	return 0;
}


void showTree(HeterogeneousTree& tree)
{
	unsigned int level = 0;
	std::queue<unsigned int> q;
	for (unsigned int i = 0; i < tree.getSize(); i++)
	{
		
		if (level == tree.getNodeLevel(i))
		{
			cout << tree.operator[]<string>(i) << "   ";
			q.push(tree.getNodeChildCount(i));
		}
		else
		{
			cout << endl;
			while (!q.empty())
			{
				int s = q.front();
				for (int j = 0; j < s; j++)
				{
					(j != s-1) ? cout << "|-------" : cout << "|";
				}
				cout << "        ";
				q.pop();
			}
			cout << endl << tree.operator[]<string>(i) << "   ";
			q.push(tree.getNodeChildCount(i));
			level++;
		}
	}
}