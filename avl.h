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
	Node *father;
	Node *left_child, *right_child;
	int height;


	Node(const T& data,const Node& father) : data(data), father(father),
	left_child(NULL), right_child(NULL), height(0)  {

	    if(this->data <= father->data)
		father->left_child = this;
	    else
		father->right_child = this;
	}

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
		if(this->data <= father->data)
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
	    return (this->data < node.data);
	}
	bool operator>(const Node& node) {
	    return (this->data > node.data);
	}
    };

    Node *root;
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
    void findVal(Node *root,T val) {

	Node *father = NULL ,*current = root;

	while( !!current && current->data != val ) {
	    father = current;
	    if(current->data < val)
		current = current->right_child;
	    else
		current = current->left_child;
	}
	throw findNodeResult(father);
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
	sizes &= (lson)? lson->data <= node->data : true;
	sizes &= (rson)? rson->data > node->data : true;


	return heights && sizes  && height_diff
	    && isAVL(lson) && isAVL(rson);
    }

public:

    AvlTree() : root(NULL) , left_most(NULL), size(0) {}

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

    void insertNode(const T val) {

	Node *father;

	try {
	    findVal(root,val);

	    /*
	     * TODO: note already exists, do something about it
	     */
	    return;
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

	if( val < left_most->data)
	    left_most = new_node;

	/*for debugging puposes, checking that the tree is still avl*/
	assert(isAVL(root) == true);
    }

    void printOrderedArray(ostream& os) {
	Node* current = left_most;


	for (int i=0; i < this->size ; i++) {
	    if( i > 0)
		current = findNextOrderedNode(current);
	    assert(current != NULL);
	    os << current->data << "(" << current->height << ") ";
	}


    }

    template <typename K,typename C>
    friend ostream& operator<<(ostream& os,const AvlTree<K,C>& tree);

    // Exceptions TODO: check neccessity
    class AVLNodeExists {};
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

