#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"

using hw1::AvlTree;
using std::ostream;

#define RUN_TEST(b)	if( (b)() ) std::cout << #b << ": [PASS]" << std::endl; \
						else std::cout << #b <<  ": [FAIL]" << std::endl;


class compare {
	public:
	bool operator() (int a,int b) {
		return (a<b);
	}
};

class getGrade {
    public:
	int operator()(int a) {
	return a;
	}
};

bool avlInsertTest () {
	AvlTree<int> tree;
	const int num_values = 1200;

	for (int i=1; i<=num_values;i++) {
		try {
			tree.insertNode(i);
		} catch (AvlTree<int>::NodeExists& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}
	if( tree.getSize() != num_values)
		return false;

	//std::cout << j << " values inserted" << std::endl;

	for(int i=num_values; i > 0; i--) {
		try {
			tree.insertNode(i);
			return false;
		} catch (AvlTree<int>::NodeExists& ex) {

		} catch (...) {
			return false;
		}
	}

/*
 *        // check that the value are ordered
 *        ostream tree_output;
 *        tree_output << tree;
 *
 *        ostream expected_output;
 *        for(int i=0; i<num_values; i++)
 *                expected_output << i << " ";
 *
 *        if ( tree_output != expected_output )
 *            return false;
 */

	/*TODO: add this check when you implement remove function*/
/*
 *        for (int i=1201,j=0; i>=0;i--) {
 *                try {
 *                        tree.removeNode(i);
 *                        j++;
 *                } catch (AVLTREE<int>::AVLNodeNotFoundException& ex) {
 *                        std::cout << "trying to reach a non-existent value" << std::endl ;
 *                } catch (...) {
 *                        return false;
 *                }
 *
 *                assert ( isEqualyBalanced<int>(tree) );
 *                assert ( isBinaryTree<int>(tree) );
 *        }
 *
 *        std::cout << j << " values removed" << std::endl;
 */

	return true;
}

bool avlFindValTest() {

	AvlTree<int> tree;
	const int num_values = 1200;

	for (int i=1; i<=num_values;i++) {
		try {
			tree.insertNode(i);
		} catch (AvlTree<int>::NodeExists& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}

	for(int i=1; i<= 2*num_values ; i++) {
		try {
		tree.findValCopyInTree(i);

		if( i>num_values)
			return false;
		} catch (AvlTree<int>::NodeDoesntExist& exc) {
		if(i<=num_values)
			return false;
		} catch (...) {
			return false;
		}

	}

	return true;
}

bool avlDeleteTest() {
	AvlTree<int> tree;
	const int num_values = 1200;

	for (int i=1; i<=num_values;i++) {
		try {
			tree.insertNode(i);
		} catch (AvlTree<int>::NodeExists& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}
	if( tree.getSize() != num_values)
		return false;

	for(int i=num_values+1; i < num_values*2; i++) {
		try {
			tree.deleteNode(i);
			return false;
		} catch (AvlTree<int>::NodeDoesntExist& ex) {

		} catch (...) {
			return false;
		}
	}

	for(int i=1; i<=(num_values/2);i++) {
		try {
			tree.deleteNode(i);
		} catch (AvlTree<int>::NodeDoesntExist& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}

	if ( tree.getSize() != (num_values/2))
		return false;


	for(int i=((num_values/2)+1); i<=num_values; i++){
		try {
			tree.deleteNode(i);
		} catch (AvlTree<int>::NodeDoesntExist& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}

	if(tree.getSize() != 0)
		return false;


	return true;
}

bool avlDeleteTest2() {

	AvlTree<int> tree;
	const int num_values = 1200;

	for (int i=1; i<=num_values;i++) {
		try {
			tree.insertNode(i);
		} catch (AvlTree<int>::NodeExists& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}
	if( tree.getSize() != num_values)
		return false;

	for(int i=1; i<=(num_values);i++) {
		try {
			tree.deleteNode(i);
		} catch (AvlTree<int>::NodeDoesntExist& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}

	if ( tree.getSize() != 0)
		return false;


	for (int i=1; i<=num_values;i++) {
		try {
			tree.insertNode(i);
		} catch (AvlTree<int>::NodeExists& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}
	if( tree.getSize() != num_values)
		return false;


	for(int i=((num_values/2)); i<num_values; i++){
		try {
			tree.deleteNode(i);
		} catch (AvlTree<int>::NodeDoesntExist& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}

	if( tree.getSize() != (num_values - (num_values - (num_values/2))) )
		return false;



    return true;
}


bool avlFindIndexTest() {

	AvlTree<int> tree;
	const int num_values = 1200;

	for (int i=0; i<=num_values;i++) {
		try {
			tree.insertNode(i);
		} catch (AvlTree<int>::NodeExists& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}
	if( tree.getSize() != num_values+1)
		return false;

	for (int i=0; i<=num_values;i++) {
		try {
			int val = tree.findValByIndex(i);
		
			if(val != i)
				return false;
		} catch (AvlTree<int>::indexIsHigherThanSize& ex) {
			return false;
		} catch (...) {
			return false;
		}
	}


	for (int i=num_values+1; i<=num_values+100;i++) {
		try {
			tree.findValByIndex(i);
			return false;
		} catch (AvlTree<int>::indexIsHigherThanSize& ex) {
		} catch (...) {
			return false;
		}
	}

    return true;
}


bool avlGetGradeTest() {

    AvlTree<int,compare,getGrade> tree;
    const int num_values = 1200;

    for (int i=0; i<=num_values;i++) {
	try {
		tree.insertNode(i);
	} catch (AvlTree<int,compare,getGrade>::NodeExists& ex) {
		return false;
	} catch (...) {
		return false;
	}
    }
    if( tree.getSize() != num_values+1)
	return false;


    for (int i=0; i<=num_values;i++) {
	try {
		int grade = tree.findGradeByIndex(i);

		int expected_grade=0;
		for(int j=0;j<=i;j++)
		expected_grade +=j;

		if(grade != expected_grade)
			return false;
	} catch (AvlTree<int,compare,getGrade>::indexIsHigherThanSize& ex) {
		return false;
	} catch (...) {
		return false;
	}
    }


    for (int i=num_values+1; i<=num_values+100;i++) {
	try {
		tree.findGradeByIndex(i);
		return false;
	} catch (AvlTree<int,compare,getGrade>::indexIsHigherThanSize& ex) {
	} catch (...) {
		return false;
	}
    }
    return true;
}



/**
int main () {

	RUN_TEST(avlInsertTest);
	RUN_TEST(avlFindValTest);
	RUN_TEST(avlDeleteTest);
	RUN_TEST(avlDeleteTest2);
	RUN_TEST(avlFindIndexTest);
	RUN_TEST(avlGetGradeTest);

 
	return 0;
}*/
