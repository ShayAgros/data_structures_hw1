    /*
 *
 *
 * 	AVL tree
 */

#ifndef avl_d
#define avl_d

#include <iostream>
#include <assert.h>

using std::ostream;
using std::endl;

namespace hw1 {

template  <typename T, typename Compare=std::less<T> >
class AvlTree {

    class Node {

	friend class AvlTree;

	T data;
	Compare compare;
	Node *father;
	Node *left_child, *right_child;
	int height;


	Node(const T& data,const Node& father) : data(data), compare(), 
	father(father), left_child(NULL), right_child(NULL), height(0)  {

	    if(compare(this->data, father->data))
		father->left_child = this;
	    else
		father->right_child = this;
	}

	Node() : data(data), father(NULL),
		left_child(NULL), right_child(NULL), height(0) { }

	Node(const T& data) : data(data), father(NULL),
	left_child(NULL), right_child(NULL), height(0) { }

	~Node() = default;


	int find_height_diff() {
	    int left_height = (left_child)? left_child->height : -1;
	    int right_height = (right_child)? right_child->height : -1;

	    return left_height - right_height;
	}


	void set_father(Node* father) {
	    this->father = father;

	    if(father) {
		if(compare(this->data, father->data))
		    father->left_child = this;
		else
		    father->right_child = this;
	    }
	}

	void update_height() {
	    int left_height = (left_child)? left_child->height : -1;
	    int right_height = (right_child)? right_child->height : -1;

	    this->height = (left_height > right_height) ?
				left_height + 1: right_height + 1;
	}

	bool operator<(const Node& node) {
	    return compare(this->data, node.data);
	}
	bool operator>(const Node& node) {
	    return compare ( node.data , this->data);
	}
	public:

		Node* getLeftChild() {
			return this->left_child;
		}

		void setLeftChild(Node* new_node) {
			if (left_child != NULL) {
				throw NodeExists();
			}
			left_child = new_node;
		}

		Node* getRightChild() {
			return this->right_child;
		}

		void setRightChild(Node* new_node) {
			if (right_child != NULL) {
				throw NodeExists();
			}
			right_child = new_node;
		}

		T& getData() {
			return this->data;
		}

		void setData(T& new_data) {
			data = new_data;
		}
    };

    Node *root;
    Compare compare;
    Node *left_most;
    int size;

    int max(int num1,int num2) {
	return (num1 > num2) ? num1 : num2;
    }
    int abs(int num) {
	return (num >= 0) ? num : -num;
    }


    void free_vertices(Node *head) {
	if(!head)
	    return;

	free_vertices(head->left_child);
	free_vertices(head->right_child);

	delete head;
    }


/*	a		b
 *    /   \	      /   \
 *   b     c	     d     a
 *  / \		          / \
 *  d  e	         e   c
 *
 */
    void rotate_right(Node *node) {
	Node *temp = node->left_child->right_child;

	node->left_child->set_father(node->father);

	node->father = node->left_child;
	node->left_child->right_child = node;

	node->left_child = temp;
	if(temp) temp->father = node;

	node->update_height();
	node->father->update_height();
    }

/*	a		c
 *    /   \	      /  \
 *   b     c	     a    e
 *  	  / \       / \
 *  	  d  e	   b   d
 *
 */
    void rotate_left(Node *node) {
	Node *temp = node->right_child->left_child;

	node->right_child->set_father(node->father);

	node->father = node->right_child;
	node->right_child->left_child = node;

	node->right_child = temp;
	if(temp) temp->father = node;

	node->update_height();
	node->father->update_height();
    }

    void do_right_rotation(Node *node) {
	if(node->left_child->find_height_diff() < 0)
	    rotate_left(node->left_child);

	rotate_right(node);
    }

    void do_left_rotation(Node *node) {
	if(node->right_child->find_height_diff() > 0)
	    rotate_right(node->right_child);

	rotate_left(node);
    }


/* The function finds the instanse of val
 * in a tree whose root is 'root' or throws
 * NodeNotFound if val doesn't exist
 *
 * @root - tree's root
 * @val - the value it looks for
 *
 * the function throws findNodeResult exception
 * if node doesn't exist
 * */
    Node* findVal(Node *root,T val) {

	Node *father = NULL ,*current = root;

	while(!!current) {
	    father = current;
	    if(compare(current->data, val)) // val > current.data
		current = current->right_child;
	    else if( compare(val, current->data) ) // val < current.data
		current = current->left_child;
	    else /*value is already in tree*/
		return current;
	}
	throw findNodeResult(father);
	return NULL;
    }

/* The function correct the avl tree
 * after inserting or removing a new node
 * @node - the node from which the avl might
 * 		be broken
 */
    void return_balance(Node *node) {
	Node *head = node;

	while (!!head) {
	    	head->update_height();
		if(head->find_height_diff() > 1)
		    do_right_rotation(head);
		else if( head->find_height_diff() < -1)
		    do_left_rotation(head);
		head = head->father;
	}
    }


/* !!!! DEBUGGING FUNCTION
 * 	checks whether the binary tree is still
 * 	an AVL tree
 */

    bool isAVL(Node* node) {
	if(!node)
	    return true;

	bool heights, sizes, height_diff;
	Node *lson,*rson;

	lson = node->left_child;
	rson = node->right_child;

	int lheight = (lson) ? lson->height : -1;
	int rheight = (rson) ? rson->height : -1;

	heights = (node->height == (max(lheight,rheight) +1));
	height_diff =  abs(lheight - rheight) <= 1;

	sizes = true;
	sizes &= (lson)? compare(lson->data, node->data) : true;
	sizes &= (rson)? compare(node->data,rson->data) : true;


	return heights && sizes  && height_diff
	    && isAVL(lson) && isAVL(rson);
    }


    /* finds next node in an 'inorder' algorithm */
    Node *findNextOrderedNode(Node *node) {
	Node* current = node;

	if(!node)
	    return NULL;

	if(node->right_child) {
	    current = current->right_child;
	    while(current->left_child)
		current = current->left_child;

	    return current;
	}

	/* TODO: is it needed? */
	if( !node->father )
	    return NULL;

	if(node->father->left_child == node)
	    return node->father;

	/* we're the right child */
	while(current && current->father && current->father->left_child != current)
	    current = current->father;
	return (current) ? current->father : NULL;
    }

    // TODO: add removing functions
public:

    AvlTree() : root(NULL), compare() , left_most(NULL), size(0) {}

	AvlTree(const AvlTree& avlTree) : root(avlTree.root), compare(avlTree.compare),
		left_most(avlTree.left_most), size(avlTree.size) {}

    ~AvlTree() {
	free_vertices(root);
    }

    /* the function checks wheather the tree is empty */
    bool isEmpty() const {
	return (size == 0);
    }

    int getSize() const {
		return size;
    }

	Node* getRoot() {
		return root;
	}

	void setRoot(Node* new_root) {
		if (root != NULL) {
			throw RootNodeExists();
		}
		root = new_root;
	}

    void insertNode(const T& val) {

	Node *father;

	try {
	    findVal(root,val);

	    /*Node exists*/
	    throw NodeExists();
	} catch(findNodeResult& ex) {
	    father = ex.getFather();
	}

	Node *new_node = new Node(val);
	size++;

	if(!root) {
	    /*empty tree*/
	    root = new_node;
	    left_most = root;
	    return;
	}

	new_node->set_father(father);

	return_balance(new_node);

	/*the balancing caused the root to change*/
	if(root->father)
	    root = root->father;

	if(compare(val, left_most->data))
	    left_most = new_node;

	/*for debugging puposes, checking that the tree is still avl*/
	assert(isAVL(root) == true);
    }

    /* finds a node whice has the value 'val'
     * and returns a reference to it
     *
     * throws NodeDoesntExist if there is no
     * such value in tree
     */
    T& findValCopyInTree(const T& val) {
	try {
	    Node* node = findVal(root,val);
	    return node->getData();

	} catch(findNodeResult& ex) {
	    /* value not found in tree */
	    throw NodeDoesntExist();
	}
    }

    void printOrderedArray(ostream& os) {
	Node* current = left_most;


	for (int i=0; i < this->size ; i++) {
	    if( i > 0)
		current = findNextOrderedNode(current);
	    assert(current != NULL);
	    os << current->data << " ";
	}


    }

    template <typename K,typename C>
    friend ostream& operator<<(ostream& os,const AvlTree<K,C>& tree);


	// Recursively inserts an array into a tree <InOrder>
	// Parameters -> 
	//			*root - the root of the current sub tree
	//			*node_array - the array we want to insert from
	//			*index - a pointer to the current index of the array
	//			*FieldFunc - the function that allows us to get the field of a value
	//			*sum_fields - a pointer to the sum of all the fields of the current sub tree
	//			*num_sons - a pointer to the num of sons in the curent sub tree
	static void recursiveIntoTree(Node* root, T* array, int* index) {
		if (root != NULL) {
			recursiveToArray(root->getLeftChild(), array, index);
			root->setData(array[*index]);
			(*index)++;
			recursiveToArray(root->getRightChild(), array, index);
		}
	}

	// Inserts an array into a tree <InOrder>
	// Parameters ->
	//			*root - the root of the current sub tree
	//			*node_array - the array we want to insert from
	//			*FieldFunc - the func that allows us to get the field of a value.
	static void ArrayToTree(AvlTree* tree, T* node_array) {
		int size = tree->getSize();
		int index, empty = 0;
		if (size > 0) {
			// The Function needs 2 int pointers, but the pointers have no
			// meaning on first call
			recursiveIntoTree(tree->getRoot, node_array, &index, &empty, &empty);
		}
	}

	// Recursively inserts nodes into the array
	// Parameters ->
	//			*root - the root of the current sub_tree
	//			*array - the array we want to insert into
	//			*index - the index of the array we want to insert to
	static void recursiveToArray(Node* root, T* array, int* index) {
		if (root != NULL) {
			recursiveToArray(root->getLeftChild(), array, index);
			array[*index] = root->getData();
			(*index)++;
			recursiveToArray(root->getRightChild(), array, index);
		}
	}

	// Inserts a tree's nodes into an array <InOrder>
	// Parameters ->
	//			*tree - the tree we want to turn into an array
	// Returns ->
	//			An array of the tree's nodes
	//			Null if an allocation failed.
	T* ToArray() {
		int index = 0;
		int size = getSize();
		T* array = new T[size];
		if (array == NULL) {
			return NULL;
		}
		recursiveToArray(getRoot(), array, &index);
		return array;
	}

	// Recursively build an empty tree
	// Parameters ->
	//			*root = the node we want to expand
	//			*size = the size of the sub_tree, not including the root
	static void recursiveEmptyTree(Node* root, int size) {
		if (size > 0) {
			int left_size = (size / 2);
			if ((size % 2) == 1) {
				left_size++;
			}
			int right_size = (size / 2);
			Node* left_node = new Node();
			if (left_node == NULL) {
				throw AvlAllocationError();
			}
			root->setLeftChild(left_node);
			recursiveEmptyTree(left_node, left_size - 1);
			if (right_size > 0) {
				Node* right_node = new Node();
				if (right_node == NULL) {
					throw AvlAllocationError();
				}
				root->setRightChild(right_node);
				recursiveEmptyTree(right_node, right_size - 1);
			}
		}
	}

	// Creates a tree without any nodes
	// Parameters ->
	//			*size - the size of the new tree
	//			*FieldFunc - the func that allows us to find the field of a value
	// Returns ->
	//			An empty Avl tree
	//			Null if an allocation failed.
	static AvlTree* BuildEmptyTree(int size) {
		AvlTree* new_tree = new AvlTree();
		if (new_tree == NULL) {
			return NULL;
		}
		if (size > 0) {
			Node* root = new Node();
			if (root == NULL) {
				delete(new_tree);
				return NULL;
			}
			new_tree->setRoot(root);
			try {
				recursiveEmptyTree(new_tree->getRoot(), size - 1);
			} catch (const RANKED_AVL_ALLOCATION_ERROR &) {
				// delete(root);
				delete(new_tree);
				return NULL;
			}
		}
		return new_tree;
	}

    // Exceptions TODO: check neccessity
    class NodeExists {};
	class RootNodeExists {};
    class NodeDoesntExist{};
	class AvlAllocationError {};

private:
    class findNodeResult {
	friend class AvlTree;

	Node* father;

	findNodeResult() : father(NULL) {}
	findNodeResult(Node* node) : father(node) { }
	Node* getFather() { return father; }
    };


}; /* end class AvlTree */

template <typename K,typename C>
ostream& operator<<(ostream& os,AvlTree<K,C>& tree) {

	tree.printOrderedArray(os);

	return os;
}

} /* end namespace */
#endif

