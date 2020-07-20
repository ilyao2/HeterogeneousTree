#include <iostream>
#include "HeterogeneousTree.h"

using namespace std;

int main()
{
	HeterogeneousTree tree;
	tree.append(1, 2);
	tree.append(77.5, 1);
	tree.append((std::string)("privet"), 1);
	tree.append(0, 0);


	HeterogeneousTree tree2 = tree;
	cout << tree2.operator[]<string>(0) << endl;
	cout << tree2.operator[]<string>(1) << endl;
	cout << tree2.operator[]<string>(2) << endl;

	return 0;
}