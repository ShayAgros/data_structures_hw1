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
	int size ;


	Node(const T& data,const Node& father) : data(data), compare(),
	father(father), left_child(NULL), right_child(NULL), height(0),
		size(1) {

	    if(compare(this->data, father->data))
		father->left_child = this;
	    else
		father->right_child = this;
	}

	Node() : data(), father(NULL),
		left_child(NULL), right_child(NULL), height(0), size(1) { }

	Node(const T& data) : data(data), father(NULL),
	left_child(NULL), right_child(NULL), height(0), size(1) { }

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

	void update_size() {

	    int left_size = (left_child)? left_child->size : 0;
	    int right_size = (right_child)? right_child->size : 0;

	    this->size = left_size + right_size + 1;
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
	Node *a = node;
	Node *b = node->left_child;

	Node *e = b->right_child;

	// update relations

	b->set_father(a->father);

	a->father = b;
	b->right_child = a;

	a->left_child = e;
	if(e) e->father = a;

	// update height and size
	a->update_height();
	a->update_size();
	a->father->update_height();
	a->father->update_size();
    }


/*	a		c
 *    /   \	      /  \
 *   b     c	     a    e
 *  	  / \       / \
 *  	  d  e	   b   d
 *
 */
    void rotate_left(Node *node) {
	Node *a = node;
	Node *c = a->right_child;

	Node *d = c->left_child;

	c->set_father(a->father);

	a->father = c;
	c->left_child = a;

	a->right_child = d;
	if(d) d->father = a;

	// update height and size
	a->update_height();
	a->update_size();
	a->father->update_height();
	a->father->update_size();
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
	    head->update_size();

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

	bool heights, sizes, height_diff, node_sizes;
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


	// checks node's sub-tree size
	int lnode_size = (lson) ? lson->size : 0;
	int rnode_size = (rson) ? rson->size : 0;

	node_sizes = ( (node->size) == (lnode_size + rnode_size + 1));

	return heights && sizes  && height_diff
	    && node_sizes && isAVL(lson) && isAVL(rson) ;
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


    Node *makeNodeALeaf(Node *node) {
	Node *leaf_node;

	if(!node->right_child && !node->left_child)
	    return node;
	else if(node->right_child && !node->left_child)
	    leaf_node = node->right_child;
	else if( !node->right_child && node->left_child)
	    leaf_node = node->left_child;
	else {
	    leaf_node = findNextOrderedNode( node );
	    T temp_ref = node->data;
	    node->data = leaf_node->data;
	    leaf_node->data = temp_ref;
	    /*now leaf_node points to the node we want to remove*/
	    return makeNodeALeaf(leaf_node);
	}

	// we can reach this section only if we had one son
	leaf_node->set_father(node->father);

	// if our node was root, we now have a new one
	if(!node->father)
	    root = leaf_node;

	return node;
    }

public:

    AvlTree() : root(NULL), compare() , left_most(NULL), size(0) {}

    AvlTree(const AvlTree& avlTree) : root(avlTree.root), compare(avlTree.compare),
    	left_most(avlTree.left_most), size(avlTree.size) {}

    ~AvlTree() {
	free_vertices(root);
    }



    /*AvlTree(const AvlTree& avlTree) : root(), compare(),
    	left_most(), size(avlTree.size) {
	if( avlTree.size == 0)
	    return;

	root = new Node();
	recursiveEmptyTree(root, size - 1, 0);

	left_most = root;
	while (left_most && left_most->left_child)
	    left_most = left_most->left_child;

	Node* src_current = avlTree.left_most;
	Node* dst_current = left_most;

	dst_current.val = src_current.val;
	for(int i=1; i < avlTree.size; i++) {
	    src_current = findNextOrderedNode(src_current);
	    dst_current = findNextOrderedNode(dst_current);
	    dst_current.val = src_current.val;
	}
    }*/

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


    void deleteNode(const T& val) {
	Node* node;	

	try {
	    node = findVal(root,val);
	    if ( node->left_child || node->right_child)
		node = makeNodeALeaf(node);

	    if (node->father) {
		if(node->father->left_child == node)
		    node->father->left_child = NULL;
		else if (node->father->right_child == node)
		    node->father->right_child = NULL;
	    }

	    return_balance(node->father);
	    if(root->father) root = root->father;

	    delete node;

	    size--;
	    root = (size > 0) ? root : NULL;

	    node = root;
	    while (node && node->left_child)
		node = node->left_child;
	    left_most = node;
	} catch(findNodeResult& ex) {
	    /* value not found in tree */
	    throw NodeDoesntExist();
	}

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
	    recursiveIntoTree(root->getLeftChild(), array, index);
	    root->setData(array[*index]);
	    (*index)++;
	    recursiveIntoTree(root->getRightChild(), array, index);
	}
    }

    // Inserts an array into a tree <InOrder>
    // Parameters ->
    //			*root - the root of the current sub tree
    //			*node_array - the array we want to insert from
    //			*FieldFunc - the func that allows us to get the field of a value.
    static void ArrayToTree(AvlTree* tree, T* node_array) {
	int size = tree->getSize();
	int index = 0;
	if (size > 0) {
	    recursiveIntoTree(tree->getRoot(), node_array, &index);
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
    void ToArray(T* array) {
	int index = 0;
	
	if( !array )
	    return;

	recursiveToArray(getRoot(), array, &index);
    }

    // Recursively build an empty tree
    // Parameters ->
    //			*root = the node we want to expand
    //			*size = the size of the sub_tree, not including the root
    static void recursiveEmptyTree(Node* root, int size, int height) {
	Node *left_node,*right_node;
	int left_size,right_size ;

	root->height = height;
	if (size > 0) {
	    left_size = (size / 2);
	    if ((size % 2) == 1) {
		left_size++;
	    }
	    right_size = (size / 2);

	    try {
		left_node = new Node();
	    } catch( std::bad_alloc& ex ) {
		throw AvlAllocationError();
	    }
	    root->setLeftChild(left_node);
	    left_node->father = root;
	    recursiveEmptyTree(left_node, left_size - 1, height + 1);
	    if (right_size > 0) {
		try {
		    right_node = new Node();
		} catch( std::bad_alloc& ex ) {
		    throw AvlAllocationError();
		}
		root->setRightChild(right_node);
		right_node->father = root;
		recursiveEmptyTree(right_node, right_size - 1, height + 1);
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

	AvlTree* new_tree;
	try {
	    new_tree = new AvlTree();
	} catch( std::bad_alloc& ex ) {
	    throw AvlAllocationError();
	}

	if (size > 0) {
	    Node* root;
	    try {
		root = new Node();
	    } catch( std::bad_alloc& ex ) {
		delete(new_tree);
		throw AvlAllocationError();
	    }

	    new_tree->setRoot(root);
	    new_tree->size = size;
	    try {
		recursiveEmptyTree(new_tree->getRoot(), size - 1, 0);
		Node* left_most = new_tree->getRoot();
		while (left_most->getLeftChild() != NULL) {
		    left_most = left_most->getLeftChild();
		}
		new_tree->left_most = left_most;
	    } catch (AvlAllocationError& exc) {
		delete(root);
		delete(new_tree);
		throw AvlAllocationError();
	    }
	}
	return new_tree;
    }


    template <typename K,typename C>
    friend ostream& operator<<(ostream& os,const AvlTree<K,C>& tree);


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

