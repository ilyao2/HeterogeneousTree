#include <iostream>
#include "HeterogeneousTree.h"

using namespace std;

void showTree(HeterogeneousTree&);

int main(int argc, char* argv[])
{
	const char* INPUT = "input";
	const char* OUTPUT = "output";
	if (argc > 1)
	{

		if (std::strcmp(argv[1], "-i")==0)
		{
			if (argc < 3)
			{
				std::cout << "Need input file name!" << endl;
				return -1;
			}
			INPUT = argv[2];
			if (argc > 3)
			{
				if (std::strcmp(argv[3], "-i") == 0)
				{
					std::cout << "Already have this parametr: " << argv[3] << endl;
					return -1;
				}
				else if (std::strcmp(argv[3], "-o") == 0)
				{
					if (argc < 5)
					{
						std::cout << "Need output file name!" << endl;
						return -1;
					}
					OUTPUT = argv[4];
				}
				else
				{
					std::cout << "Unknowing parametr: " << argv[3] << endl;
					return -1;
				}
			}

		}
		else if (std::strcmp(argv[1], "-o") == 0)
		{
			if (argc < 3)
			{
				std::cout << "Need output file name!" << endl;
				return -1;
			}
			OUTPUT = argv[2];
			if (argc > 3)
			{
				if (std::strcmp(argv[3], "-i") == 0)
				{
					if (argc < 5)
					{
						std::cout << "Need input file name!" << endl;
						return -1;
					}
					INPUT = argv[4];

				}
				else if (std::strcmp(argv[3], "-o") == 0)
				{
					std::cout << "Already have this parametr: " << argv[3] << endl;
					return -1;
				}
				else
				{
					std::cout << "Unknowing parametr: " << argv[3] << endl;
					return -1;
				}
			}
		}
		else
		{
			std::cout << "Unknowing parametr: " << argv[1] << endl;
			return -1;
		}
	}
	HeterogeneousTree tree;
	try
	{
		tree.deserialize(INPUT);
	}
	catch (const std::exception&)
	{
		std::cout << "Can't deserialize" << endl;
		return -1;
	}
	showTree(tree);


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
			std::cout << tree.operator[]<string>(i) << "   ";
			q.push(tree.getNodeChildCount(i));
		}
		else
		{
			std::cout << endl;
			while (!q.empty())
			{
				int s = q.front();
				for (int j = 0; j < s; j++)
				{
					(j != s-1) ? std::cout << "|-------" : std::cout << "|";
				}
				std::cout << "        ";
				q.pop();
			}
			std::cout << endl << tree.operator[]<string>(i) << "   ";
			q.push(tree.getNodeChildCount(i));
			level++;
		}
	}
}