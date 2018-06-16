#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstddef>
#include <exception>

namespace hw2 {

template<typename KeyType, typename ValueType>
class Linked_List {
protected:

	class Node {

		KeyType m_key;
		ValueType m_value;
		Node* m_next;

	public:

		// C'tor
		Node(KeyType const &key, ValueType const &value) :
			m_key(key), m_value(value), m_next(NULL) {
		}

		// Default C'tor (for ghost)
		Node() {
			m_next = NULL;
		}

		// D'tor
		~Node() {
		}

		// Returns the key of the node
		KeyType const& GetKey() const {
			return m_key;
		}

		// Returns the value of the node
		ValueType& GetValue() {
			return m_value;
		}

		// Returns the next node
		Node* GetNext() const {
			return m_next;
		}

		// Sets the Key to the given key
		// Parameters ->
		//		*key -> the key we want to change to
		void SetKey(const KeyType& key) {
			m_key = key;
		}

		// Sets the Value to the given value
		// Parameters ->
		//		*value -> the value we want to change to
		void SetValue(const ValueType& value) {
			m_value = value;
		}

		// Sets the next node
		// Parameters ->
		//		*next - the new node we want to link to
		void SetNext(Node* next) {
			m_next = next;
		}

	}; // Node

public:
	// An iterator. Used to iterate over the nodes in a list. At every given
	// moment, the iterator points to one of the nodes in the list
	class iterator {
	public:
		// Constructs a new iterator that points to the start of the list
		//
		// @param list the list over which the iterator iterates.
		iterator(Linked_List* list) : m_current(list->m_ghost), m_list(list) {
		}

		// A copy constructor.
		//
		// @param it the iterator to copy.
		iterator(const iterator& it) :
			m_current(it.m_current), m_list(it.m_list) {
		}

		// A destructor.
		~iterator() {
		}

		// Moves the iterator to point to the next node
		//
		// @return a reference to *this (the same iterator) after moving it.
		// @throw ITER_REACHED_END if current node is NULL;
		iterator& Next() {
			if (m_current == NULL) {
				throw IterReachedEndException();
			}
			m_current = m_current->GetNext();
			return *this;
		}

		// Returns the value of the node the iterator points to
		// @throw ITER_REACHED_END if current node is NULL;
		ValueType GetValue() const {
			if (m_current == NULL) {
				throw IterReachedEndException();
			}
			return m_current->GetValue();
		}

		// Sets the value of the node the iterator points to
		// @throw ITER_REACHED_END if current node is NULL;
		void SetValue(const ValueType& value) {
			if (m_current == NULL) {
				throw IterReachedEndException();
			}
			m_current->SetValue(value);
		}

		// Sets the key of the node the iterator points to
		// @throw ITER_REACHED_END if current node is NULL;
		void SetKey(const KeyType& key) {
			if (m_current == NULL) {
				throw IterReachedEndException();
			}
			m_current->SetKey(key);
		}

		// Assigment operator.
		// Parameters->
		//		*rhs - The iterator we want to assign.
		const iterator& operator=(const iterator& rhs) {
			if (*this != rhs) {
				m_current = rhs.m_current;
				m_list = rhs.m_list;
			}
			return *this;
		}

		// Dereference operator. Return the key of the node pointed by the iterator.
		//
		// @return the key of the node to which the iterator points.
		// @throw ITER_REACHED_END if current node is NULL;
		KeyType operator*() const {
			if (m_current == NULL) {
				throw IterReachedEndException();
			}
			return m_current->GetKey();
		}

		// Equal operator. Two iterators are equal if they point to the same
		// node in the same list
		//
		// @param rhs righ hand side operand.
		// @return true if the iterators are equal.
		bool operator==(const iterator& rhs) const {
			return ((m_current == rhs.m_current) && (m_list == rhs.m_list));
		}

		// Not equal operator (see definition of equality above).
		//
		// @param rhs righ hand side operand.
		// @return true if the iterators are not equal.
		bool operator!=(const iterator& rhs) const {
			return !(*this == rhs);
		}

	private:
		Node* m_current;
		Linked_List* m_list;
	}; // Iterator

	// C'tor
	Linked_List() {
		m_ghost = new Node();
	}

	// D'tor
	~Linked_List() {
		Node* current_node = m_ghost;
		Node* next = m_ghost->GetNext();
		delete(m_ghost);
		if (next != NULL) {
			while (next->GetNext() != NULL) {
				current_node = next;
				next = next->GetNext();
				delete(current_node);
			}
		}
		delete(next);
	}

	// Returns whether a node with the given key exists
	// Parameters ->
	//			*key - the key we want to find
	// Returns ->
	//			true if the node with the key exists.
	//			false otherwise.
	bool doesExist(const KeyType &key) const {
		Node* current_node = m_ghost->GetNext();
		while (current_node != NULL) {
			if (current_node->GetKey() == key) {
				return true;
			}
			current_node = current_node->GetNext();
		}
		return false;
	}

	// Returns the value of the node with the given key/
	// Parameters ->
	//			*key - the key of the node we want to find.
	// Returns ->
	//			the value of the node with the given key.
	// Throws ->
	//			LIST_KEY_DOESNT_EXIST - if a node with the given key does not exist.
	ValueType& find(const KeyType &key) {

		if (!doesExist(key)) {
			throw ListKeyDoesntExistException();
		}

		Node* current_node = m_ghost->GetNext();

		while (current_node != NULL) {
			if (current_node->GetKey() == key) {
				return current_node->GetValue();
			}
			current_node = current_node->GetNext();
		}

		throw ListKeyDoesntExistException();
	}

	// Inserts a new node with the given key and value.
	// Parameters ->
	//			*key - the key of the new node.
	//			*value - the value of the new node.
	// Throws ->
	//			LIST_KEY_ALREADY_EXISTS - if a node with the given key already exists.
	//			LIST_ALLOCATION_ERROR - if an allocation failed.
	void insert(const KeyType &key, const ValueType &value) {
		if (doesExist(key)) {
			throw ListKeyAlreadyExistsException();
		}
		Node* next_node = m_ghost->GetNext();
		Node* new_node = new Node(key, value);
		if (new_node == NULL) {
			throw ListAllocationException();
		}
		new_node->SetNext(next_node);
		m_ghost->SetNext(new_node);
	}

	// Removes the node with the given key
	// Parameters ->
	//			*key - the key of the node we want to remove.
	// Throws ->
	//			LIST_KEY_DOESNT_EXIST - if a node with the given key does not exist.
	void remove(const KeyType &key) {
		if (!doesExist(key)) {
			throw ListKeyDoesntExistException();
		}
		Node* current_node = m_ghost;
		while ((current_node->GetNext())->GetKey() != key) {
			current_node = current_node->GetNext();
		}
		Node* node_to_remove = current_node->GetNext();
		current_node->SetNext(node_to_remove->GetNext());
		delete(node_to_remove);
	}

	class IterException : public std::exception {
	};
	class IterReachedEndException : public IterException {
	};
	class ListException : public std::exception {
	};
	class ListAllocationException : public ListException {
	};
	class ListKeyAlreadyExistsException : public ListException {
	};
	class ListKeyDoesntExistException : public ListException {
	};
private:
	Node* m_ghost;
};


} /* end namespace */
#endif
