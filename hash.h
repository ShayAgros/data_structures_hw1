#ifndef HASH_H
#define HASH_H

#include "linked_list.h"
#include <exception>

class HASH_RESULT : public std::exception {
};
class HASH_ALREADY_MEMBER : public HASH_RESULT {
};
class HASH_NOT_A_MEMBER : public HASH_RESULT {
};
class HASH_ALLOCATION_ERROR : public HASH_RESULT {
};

const static int NOT_FOUND = -1;
const static int default_size = 8;

template<typename KeyType, typename ValueType>
class Hash {	
public:

	// C'tor
	Hash(int(*hash_func)(KeyType, int)) : m_size(default_size),
		m_sum_of_obj(0), m_HashFunc(hash_func) {
		m_table = new Linked_List<KeyType, ValueType>*[m_size];
		for (int i = 0; i < m_size; i++) {
			m_table[i] = new Linked_List<KeyType, ValueType>();
		}
	}

	// We dont want a Copy C'tor
	Hash(const Hash& hash_table) = delete;

	// D'tor
	~Hash() {
		for (int i = 0; i < m_size; i++) {
			delete(m_table[i]);
		}
		delete[] m_table;
	}

	// Finds and returns the value of the requested object.
	// Parameters ->
	//			*key - the key of the object we want to find.
	// Returns ->
	//			The object if it exists in the hash table.
	// Throws ->
	//			HASH_NOT_A_MEMBER if the object does not exist in the table
	ValueType Find(const KeyType &key) const {
		int index = m_HashFunc(key, m_size);
		Linked_List<KeyType, ValueType>* list = m_table[index];
		if (!(list->DoesExist(key))) {
			throw HASH_NOT_A_MEMBER();
		}
		return list->Find(key);
	}

	// Returns whether an object with the given key exists
	// Parameters ->
	//			*key - the key of the object we want to find.
	// Returns ->
	//			true if an object with the given key exists.
	//			false otherwise.
	bool DoesExist(const KeyType &key) const {
		int index = m_HashFunc(key, m_size);
		Linked_List<KeyType, ValueType>* list = m_table[index];
		return list->DoesExist(key);
	}

	// Inserts an object into the hash table
	// If the array becomes completely full, increase the size of the array by 2.
	// Parameters ->
	//			*obj - the object we want to add.
	// Throws ->
	//			HASH_ALREADY_MEMBER - if the object as already been added.
	//			HASH_ALLOCATION_ERROR - if an alllocation failed.
	void Insert(const KeyType &key, const ValueType &value) {
		if (DoesExist(key)) {
			throw HASH_ALREADY_MEMBER();
		}
		int index = m_HashFunc(key, m_size);
		Linked_List<KeyType, ValueType>* list = m_table[index];
		try {
			list->Insert(key, value);
		} catch (const LIST_ALLOCATION_ERROR&) {
			throw HASH_ALLOCATION_ERROR();
		}
		m_sum_of_obj++;
		if (m_sum_of_obj == m_size) {
			ResizeTable(m_size * 2);
		}
	}

	// Removes an object from the hash table.
	// If the table is only quarter full, decrease its size by 2.
	// Parameters ->
	//			*key - the object we want to remove
	// Throws ->
	//			HASH_NOT_A_MEMBER - if the object is not a member of the hash table.
	void Remove(const KeyType &key) {
		if (!DoesExist(key)) {
			throw HASH_NOT_A_MEMBER();
		}
		int index = m_HashFunc(key, m_size);
		Linked_List<KeyType, ValueType>* list = m_table[index];
		list->Remove(key);
		m_sum_of_obj--;
		if ((m_sum_of_obj <= (m_size / 4)) && (m_size > default_size)) {
			ResizeTable(m_size / 2);
		}
	}

	// Iterates over the whole hash table, and performs a certain function on all the objects.
	// Parameters ->
	//			*IterFunc - the function that we want to perform on all the objects.
	void IterateOverHash(void(*IterFunc)(ValueType)) {
		for (int i = 0; i < m_size; i++) {
			typename Linked_List<KeyType, ValueType>::iterator iter =
				typename Linked_List<KeyType, ValueType>::iterator(m_table[i]);
			bool reached_end = false;
			iter.Next();
			while (!reached_end) {
				ValueType value;
				try {
					value = iter.GetValue();
					IterFunc(value);
					iter.Next();
				} catch (const ITER_REACHED_END&) {
					reached_end = true;
				}
			}
		}
	}

private:
	int m_size;
	int m_sum_of_obj;
	int(*m_HashFunc)(KeyType, int);
	Linked_List<KeyType, ValueType>** m_table;

	// Changes the size of the array and relocates all the objects.
	// Throws ->
	//			HASH_ALLOCATION_ERROR - if an allocation failed
	void ResizeTable(int new_size) {
		Linked_List<KeyType, ValueType>** new_table =
			new Linked_List<KeyType, ValueType>*[new_size];
		if (!new_table) {
			throw HASH_ALLOCATION_ERROR();
		}
		for (int i = 0; i < new_size; i++) {
			new_table[i] = new Linked_List<KeyType, ValueType>();
			if (!new_table[i]) {
				throw HASH_ALLOCATION_ERROR();
			}
		}
		Linked_List<KeyType, ValueType>** old_table = m_table;
		int old_size = m_size;
		m_table = new_table;
		m_size = new_size;
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
					new_index = m_HashFunc(key, new_size);
					iter.Next();
					new_table[new_index]->Insert(key, value);
					old_table[i]->Remove(key);
				} catch (const ITER_REACHED_END&) {
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

#endif /** HASH_H **/