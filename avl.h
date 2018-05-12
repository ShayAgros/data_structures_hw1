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
	    return node->data;

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

    // Exceptions TODO: check neccessity
    class NodeExists {};
    class NodeDoesntExist{};

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

