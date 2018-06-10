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
public:
	class Node {
	private:
		int _index;
		T _data;
	public:
		Node(int index, const T& data) : _index(index), _data(data) {}
		~Node() {}

		int getIndex() { return _index; }
		const T& getData() { return _data; }
		void setIndex(int index) { _index = index; }
		void setData(const T& data) { _data = data; }
	};

private:
	Node** _heap;
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
		Node* temp = _heap[i];
		_heap[i] = _heap[j];
		_heap[j] = temp;
		_heap[i]->setIndex(i);
		_heap[j]->setIndex(j);
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

			if (left_index < size && compare(_heap[left_index]->getData(), 
				_heap[i]->getData())) {
				min_index = left_index;
			}
			if (right_index < size && compare(_heap[right_index]->getData(), 
				_heap[min_index]->getData())) {
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
		while ((father_index != -1) && compare(_heap[i]->getData(), _heap[father_index]->getData())) {
			swap(i, father_index);
			i = father_index;
			father_index = getFatherIndex(i);
		}		
	}

public:
	MinHeap() : _heap(NULL), _size(0), _array_size(0), _compare() {}

	~MinHeap() {
		if (_heap != NULL) {
			for (int i = 0; i < _size; i++) {
				if (_heap[i] != NULL) {
					delete _heap[i];
					_heap[i] = NULL;
				}
			}
			delete[] _heap;
			_heap = NULL;
		}
	}

	MakeHeap(int n, T* arr) {
		if (_heap != NULL) {
			HeapAlreadyExistsException();
		}
		_size = n;
		_array_size = pow(2, (int)log(n) + 1);
		_heap = new Node*[_array_size];

		for (int i = 0; i < _size_array; i++) {
			_heap[i] = NULL;
			if (i < _size) {
				_heap[i] = new Node(i, arr[i]);
			}
		}

		for (int i = ((size / 2) - 1); i >= 0; i--) {
			siftDown(i);
		}
	}

	void resizeHeap() {
		_array_size *= 2;
		Node** new_heap = new Node*[_array_size];
		for (int i = 0; i < _size; i++) {
			new_heap[i] = _heap[i];
		}
		delete[] _heap;
		_heap = new_heap;
	}

	void insert(const T& x) {
		if (_size == _array_size) {
			resizeHeap()
		}
		_heap[_size] = new Node(_size, x);
		_size++;
		siftUp(_size - 1);
	}

	void decKey(int index, const T& value) {
		if (compare(value, _heap[i]->getData())) {
			_heap[i]->setData(value);
		}
		siftUp(index);
	}

	void delMin() {
		if (_size == 0) {
			return;
		}
		delete _heap[0];
		_heap[0] = _heap[_size - 1];
		_heap[0]->setIndex(0);
		_heap[_size - 1] = NULL;
		_size--;
		if (_size > 0) {
			siftDown(0);
		}
	}

	const T& findMin() {
		return _heap[0]->getData();
	}
	
	class HeapOutOfBandException {};
	class HeapAlreadyExistsException {};


}; /* end class MinHeap */



} /* end namespace */
#endif

