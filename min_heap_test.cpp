#include "min_heap.h"

#include <iostream>
#include <stdlib.h>
#include <assert.h>

using hw1::MinHeap;
using std::ostream;

#define RUN_TEST(b)	if( (b)() ) std::cout << #b << ": [PASS]" << std::endl; \
						else std::cout << #b <<  ": [FAIL]" << std::endl;


bool heapMakeHeapTest() {
	int nums[] = {5,1,2,4,3};
	MinHeap<int> min_heap;
	min_heap.MakeHeap(5, nums);
	min_heap.decKey(0, -10);
	return min_heap.findMin() == -10;
}

bool heapInsertDeleteTest() {
	MinHeap<int> heap;
	const int num_values = 1200;

	for (int i = 1; i <= num_values;i++) {
		try {
			heap.insert(i);
		} catch (...) {
			return false;
		}
	}

	for (int i = 1; i <= num_values;i++) {
		if (heap.findMin() != i) {
			return false;
		}
		heap.delMin();
	}
	return true;
}


int main() {

	RUN_TEST(heapMakeHeapTest);
	RUN_TEST(heapInsertDeleteTest);

	return 0;
}
