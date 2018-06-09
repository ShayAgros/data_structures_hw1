/*
*
*
* 	Minimum Heap
*/

#ifndef min_healp_d
#define min_heap_d

#include <iostream>
#include <assert.h>
#include <math.h>

namespace hw1 {

template  <typename T, typename Compare=std::less<T>>
class MinHeap {

private:
	T* _heap;
	int _size, _array_size;
	Compare _compare;

	int getLeftSonIndex(int i) {
		return 2 * i + 1;
	}

	int getRightSonIndex(int i) {
		return 2 * (i + 1);
	}

	int getFatherIndex(int i) {
		return (i - 1) / 2;
	}

	bool isLeaf(int i) {
		return (i + 1) * 2 > _size;
	}

	void swap(int i, int j) {
		T temp = _heap[i];
		_heap[i] = _heap[j];
		_heap[j] = temp;
	}

	void siftDown(int i) {
		bool flag = true;
		if (i >= _size) {
			throw HeapOutOfBandException();
		}
		while (flag) {
			int min_index = i;
			int left_index = getLeftSonIndex(i);
			int right_index = getRightSonIndex(i);

			if (left_index < size && compare(_heap[left_index], _heap[i])) {
				min_index = left_index;
			}
			if (right_index < size && compare(_heap[right_index], _heap[min_index])) {
				min_index = right_index;
			}
			if (min_index != i) {
				swap(i, min_index);
				i = min_index;
			} else {
				flag = false;
			}
		}
	}

	void siftUp(int i) {
		if (i >= _size) {
			throw HeapOutOfBandException();
		}
		int father_index = getFatherIndex(i);
		while ((father_index != -1) && compare(_heap[i], _heap[father_index])) {
			swap(i, father_index);
			i = father_index;
			father_index = getFatherIndex(i);
		}		
	}

public:
	MinHeap() : _heap(NULL), _size(0), _array_size(0), _compare() {}

	~MinHeap() {
		if (_heap != NULL) {
			delete[] _heap;
		}
	}

	MakeHeap(int n, T* arr) {
		if (_heap != NULL) {
			HeapAlreadyExistsException();
		}
		_size = n;
		_array_size = pow(2, (int)log(n) + 1);
		_heap = new T[_array_size];

		for (int i = 0; i < _size_array; i++) {
			if (i < n) {
				_heap[i] = arr[i];
			}
		}

		for (int i = ((size / 2) - 1); i >= 0; i--) {
			siftDown(i);
		}
	}

	void resizeHeap() {
		_array_size *= 2;
		T* new_heap = new T[_array_size];
		for (int i = 0; i < _size; i++) {
			new_heap[i] = _heap[i];
		}
		delete[] _heap;
		_heap = new_heap;
	}

	void insert(T& x) {
		if (_size == _array_size) {
			resizeHeap()
		}
		_heap[_size] = x;
		_size++;
		siftUp(_size - 1);
	}

	void decKey(int index, T& value) {
		if (compare(value, _heap[i])) {
			_heap[i] = value;
		}
		siftUp(index);
	}

	void delMin() {
		if (_size == 0) {
			return;
		}
		_heap[0] = _heap[_size - 1];
		_size--;
		if (_size > 0) {
			siftDown(0);
		}
	}


	class HeapOutOfBandException {};
	class HeapAlreadyExistsException {};


}; /* end class MinHeap */



} /* end namespace */
#endif

