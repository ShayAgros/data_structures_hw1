#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "avl.h"

using hw1::AvlTree;
using std::ostream;

#define RUN_TEST(b)	if( (b)() ) std::cout << #b << ": [PASS]" << std::endl; \
						else std::cout << #b <<  ": [FAIL]" << std::endl;


bool avlInsertTest () {
	AvlTree<int> tree;
	const int num_values = 1200;

	for (int i=1; i<=num_values;i++) {
		try {
			tree.insertNode(i);
		} catch (AvlTree<int>::AVLNodeExists& ex) {
		    return false;
		} catch (...) {
		    return false;
		}
	}

	//std::cout << j << " values inserted" << std::endl;

	for(int i=num_values; i > 0; i--) {
	    try {
		tree.insertNode(i);
		return false;
	    } catch (AvlTree<int>::AVLNodeExists& ex) {

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



int main () {

	RUN_TEST(avlInsertTest);

	return 0;
}
