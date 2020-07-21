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


	int s1 = -1;
	while (s1 != 0)
	{
		system("cls");
		cout << "1 - show" << endl;
		cout << "2 - getElemByIndex" << endl;
		cout << "3 - append int" << endl;
		cout << "4 - append double" << endl;
		cout << "5 - append std::string" << endl;
		cout << "6 - clear" << endl;
		cout << "7 - getSize" << endl;
		cout << "8 - serialize" << endl;
		cout << "9 - deserialize" << endl;
		cout << "10 - isEmpty" << endl;
		cout << "11 - getNodeLevel" << endl;
		cout << "12 - getNodeChildCount" << endl;
		cout << "0 - Exit" << endl;
		cout << "--->  ";
		cin >> s1;
		unsigned int index = 0;
		int intVal = 0;
		double doubleVal = 0;
		string stringVal = "";
		int childCount = 0;
		HeterogeneousTree temp;
		switch (s1)
		{
		case 1:
			system("cls");
			showTree(tree);
			cout << endl;
			system("pause");
			break;
		case 2:
			system("cls");
			cout << "input index: ";
			cin >> index;
			system("cls");
			try
			{
				cout << tree.getValue<string>(index) << endl;
			}
			catch (const std::exception& e)
			{
				cout << "Erorr!" << endl << e.what() << endl;
				system("pause");
				break;
			}
			system("pause");
			break;
		case 3:
			system("cls");
			cout << "input value: ";
			cin >> intVal;
			cout << "input childCount: ";
			cin >> childCount;
			try
			{
				tree.append(intVal, childCount);
			}
			catch (const std::exception& e)
			{
				cout << "Erorr!" << endl << e.what() << endl;
				system("pause");
				break;
			}
			break;
		case 4:
			system("cls");
			cout << "input value: ";
			cin >> doubleVal;
			cout << "input childCount: ";
			cin >> childCount;
			try
			{
				tree.append(doubleVal, childCount);
			}
			catch (const std::exception& e)
			{
				cout << "Erorr!" << endl << e.what() << endl;
				system("pause");
				break;
			}
			break;
		case 5:
			system("cls");
			cout << "input value: ";
			cin >> stringVal;
			cout << "input childCount: ";
			cin >> childCount;
			try
			{
				tree.append(stringVal, childCount);
			}
			catch (const std::exception& e)
			{
				cout << "Erorr!" << endl << e.what() << endl;
				system("pause");
				break;
			}
			break;
		case 6:
			system("cls");
			tree.clear();
			cout << "Cleared" << endl;
			system("pause");
			break;
		case 7:
			system("cls");
			cout << "Size: " << tree.getSize() << endl;
			system("pause");
			break;
		case 8:
			system("cls");
			try
			{
				tree.serialize(OUTPUT);
			}
			catch (const std::exception& e)
			{
				tree = temp;
				cout << "Can't serialize!" << endl << e.what() << endl;
				system("pause");
				break;
			}
			cout << "serialized!" << endl;
			system("pause");
			break;
		case 9:
			system("cls");
			temp = tree;
			try
			{
				tree.deserialize(INPUT);
			}
			catch (const std::exception& e)
			{
				tree = temp;
				cout << "Can't deserialize!" << endl << e.what() << endl;
				system("pause");
				break;
			}
			cout << "deserialized!" << endl;
			system("pause");
			break;
		case 10:
			system("cls");
			cout << ((tree.isEmpty()) ? "Empty" : "Not Empty") << endl;
			system("pause");
			break;
		case 11:
			system("cls");
			cout << "input index: ";
			cin >> index;
			system("cls");
			try
			{
				cout << tree.getNodeLevel(index) << endl;
			}
			catch (const std::exception& e)
			{
				cout << "Erorr!" << endl << e.what() << endl;
				system("pause");
				break;
			}
			system("pause");
			break;
		case 12:
			system("cls");
			cout << "input index: ";
			cin >> index;
			system("cls");
			try
			{
				cout << tree.getNodeChildCount(index) << endl;
			}
			catch (const std::exception& e)
			{
				cout << "Erorr!" << endl << e.what() << endl;
				system("pause");
				break;
			}
			system("pause");
			break;
		case 0:
			system("cls");
			break;
		default:
			system("cls");
			cout << "Unknowing command!" << endl;
			system("pause");
			break;
		}
	}

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
			std::cout << tree.getValue<string>(i) << "   ";
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
			std::cout << endl << tree.getValue<string>(i) << "   ";
			q.push(tree.getNodeChildCount(i));
			level++;
		}
	}
}