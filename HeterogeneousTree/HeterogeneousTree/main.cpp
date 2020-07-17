#include <iostream>
#include "HeterogeneousTree.h"

using namespace std;

int main()
{
	HeterogeneousTree tree;
	tree.append(1, 2);
	tree.append(0.5, 1);
	tree.append((std::string)("privet"), 1);
	tree.append(0, 0);


	return 0;
}