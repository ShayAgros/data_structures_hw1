#ifndef HASH_H
#define HASH_H

#include "linked_list.h"
#include <exception>

namespace hw1 {

const static int NOT_FOUND = -1;
const static int DEFAULT_SIZE = 8;

template<typename KeyType, typename ValueType>
class Hash {	

// abbreviate some common names
typedef Linked_List<KeyType, ValueType> LinkedListClass;

public:

	// C'tor
	Hash(int(*hash_func)(KeyType, int)) : _size(DEFAULT_SIZE),
		_sum_of_obj(0), _HashFunc(hash_func) {
		_table = new Linked_List<KeyType, ValueType>*[_size];
		for (int i = 0; i < _size; i++) {
			_table[i] = new Linked_List<KeyType, ValueType>();
		}
	}

	// We dont want a Copy C'tor
	Hash(const Hash& hash_table) = delete;

	// D'tor
	~Hash() {
		for (int i = 0; i < _size; i++) {
			delete(_table[i]);
		}
		delete[] _table;
	}

	// Finds and returns the value of the requested object.
	// Parameters ->
	//			*key - the key of the object we want to find.
	// Returns ->
	//			The object if it exists in the hash table.
	// Throws ->
	//			HashNotAMemberException if the object does not exist in the table
	ValueType& find(const KeyType &key) {
		int index = _HashFunc(key, _size);
		Linked_List<KeyType, ValueType>* list = _table[index];
		if (!(list->doesExist(key))) {
			throw HashNotAMemberException();
		}
		return list->find(key);
	}

	// Returns whether an object with the given key exists
	// Parameters ->
	//			*key - the key of the object we want to find.
	// Returns ->
	//			true if an object with the given key exists.
	//			false otherwise.
	bool doesExist(const KeyType &key) const {
		int index = _HashFunc(key, _size);
		Linked_List<KeyType, ValueType>* list = _table[index];
		return list->doesExist(key);
	}

	// Inserts an object into the hash table
	// If the array becomes completely full, increase the size of the array by 2.
	// Parameters ->
	//			*obj - the object we want to add.
	// Throws ->
	//			HashAlreadyMemberException - if the object as already been added.
	//			HashAllocationException - if an alllocation failed.
	void insert(const KeyType &key, const ValueType &value) {
		if (doesExist(key)) {
			throw HashAlreadyMemberException();
		}
		int index = _HashFunc(key, _size);
		Linked_List<KeyType, ValueType> *list = _table[index];
		try {
			list->insert(key, value);
		} catch (typename LinkedListClass::ListAllocationException &exc) {
			throw HashAllocationException();
		}
		_sum_of_obj++;
		if (_sum_of_obj == _size) {
			resizeTable(_size * 2);
		}
	}

	// Removes an object from the hash table.
	// If the table is only quarter full, decrease its size by 2.
	// Parameters ->
	//			*key - the object we want to remove
	// Throws ->
	//			HashNotAMemberException - if the object is not a member of the hash table.
	void remove(const KeyType &key) {
		if (!doesExist(key)) {
			throw HashNotAMemberException();
		}
		int index = _HashFunc(key, _size);
		Linked_List<KeyType, ValueType>* list = _table[index];
		list->remove(key);
		_sum_of_obj--;
		if ((_sum_of_obj <= (_size / 4)) && (_size > DEFAULT_SIZE)) {
			resizeTable(_size / 2);
		}
	}


	class HashException : public std::exception {
	};
	class HashAlreadyMemberException : public HashException {
	};
	class HashNotAMemberException : public HashException {
	};
	class HashAllocationException : public HashException {
	};

private:
	int _size;
	int _sum_of_obj;
	int(*_HashFunc)(KeyType, int);
	Linked_List<KeyType, ValueType>** _table;

	// Changes the size of the array and relocates all the objects.
	// Throws ->
	//			HashAllocationException - if an allocation failed
	void resizeTable(int new_size) {

		Linked_List<KeyType, ValueType>** new_table =
			new Linked_List<KeyType, ValueType>*[new_size];

		if (!new_table) {
			throw HashAllocationException();
		}
		for (int i = 0; i < new_size; i++) {
			new_table[i] = new Linked_List<KeyType, ValueType>();
			if (!new_table[i]) {
				throw HashAllocationException();
			}
		}
		Linked_List<KeyType, ValueType>** old_table = _table;
		int old_size = _size;
		_table = new_table;
		_size = new_size;
		for (int i = 0; i < old_size; i++) {
			typename Linked_List<KeyType, ValueType>::iterator iter =
				typename Linked_List<KeyType, ValueType>::iterator(old_table[i]);

			bool reached_end = false;
			iter.Next();
			// sum_of_obj?
			while (!reached_end) {
				KeyType key;
				ValueType value;
				int new_index;
				try {
					key = *iter;
					value = iter.GetValue();
					new_index = _HashFunc(key, new_size);
					iter.Next();
					new_table[new_index]->insert(key, value);
					old_table[i]->remove(key);
				} catch (typename LinkedListClass::IterReachedEndException& exc) {
					reached_end = true;
				}
			}
		}
		for (int j = 0; j < old_size; j++) {
			delete(old_table[j]);
		}
		delete[] old_table;
	}
}; //template


} /* end namespace */

#endif /** HASH_H **/
