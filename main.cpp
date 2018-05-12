#include <iostream>
#include "avl.h"


using std::cout;
using hw1::AvlTree;

int main(int argc, char **argv) {
    	AvlTree<int> tree;


	for (int i = 0; i<100; i++)
	    tree.insertNode(i);

	for(int i=200; i>101;i--)

	    tree.insertNode(i);

	cout << tree << std::endl;

	return 0;
}
