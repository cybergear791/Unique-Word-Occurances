//Header File created by Dr.Ravikumar 2012

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iomanip>
#include <iostream>    // For NULL
using namespace std;

// BinarySearchTree class
//
// CONSTRUCTION: with ITEM_NOT_FOUND object used to signal failed finds
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
//void findWord( x )	  --> linenumber
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
public:
	BinarySearchTree() :root(NULL)
	{
	}

	BinarySearchTree(const BinarySearchTree & rhs) : root(NULL)
	{
		*this = rhs;
	}

	/**
	* Destructor for the tree
	*/
	~BinarySearchTree()
	{
		makeEmpty();
	}

	/**
	* Find the smallest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const Comparable & findMin() const
	{
		
		return findMin(root)->element;
	}

	/**
	* Find the largest item in the tree.
	* Throw UnderflowException if empty.
	*/
	const Comparable & findMax() const
	{

		return findMax(root)->element;
	}

	void findWord(const Comparable & word)  //////////////////////////
	{
		return findWord(word, root);
	}

	/**
	* Returns true if x is found in the tree.
	*/
	bool contains(const Comparable & x) const
	{
		return contains(x, root);
	}

	/**
	* Test if the tree is logically empty.
	* Return true if empty, false otherwise.
	*/
	bool isEmpty() const
	{
		return root == NULL;
	}

	/**
	* Print the tree contents in sorted order.
	*/
	void printTree(ostream & out = cout) const
	{
		if (isEmpty())
			out << "Empty tree" << endl;
		else
			printTree(root, out);
	}

	/**
	* Make the tree logically empty.
	*/
	void makeEmpty()
	{
		makeEmpty(root);
	}

	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(const Comparable & x, string & linenumber)
	{
		insert(x, root, linenumber);
	}
	/**
	* Insert x into the tree; duplicates are ignored.
	*/
	void insert(Comparable && x, string & linenumber)
	{
		insert(std::move(x), root, linenumber);
	}
	/**
	* Remove x from the tree. Nothing is done if x is not found.
	*/
	void remove(const Comparable & x)
	{
		remove(x, root);
	}

	/**
	* Deep copy.
	*/
	const BinarySearchTree & operator=(const BinarySearchTree & rhs)
	{
		if (this != &rhs)
		{
			makeEmpty();
			root = clone(rhs.root);
		}
		return *this;
	}

private:
	struct BinaryNode
	{
		Comparable element;
		BinaryNode *left;
		BinaryNode *right;
		string linenumber;
		BinaryNode(const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, string & Slinenumber)
			: element(theElement), left(lt), right(rt), linenumber(Slinenumber) { }
	};

	BinaryNode *root;


	/**
	* Internal method to insert into a subtree.
	* x is the item to insert.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void insert(const Comparable & x, BinaryNode * & t,string & linenumber)
	{
		if (t == NULL)
			t = new BinaryNode(x, NULL, NULL, linenumber);
		else if (x < t->element)
			insert(x, t->left, linenumber);
		else if (t->element < x)
			insert(x, t->right, linenumber);
		else
			t->linenumber += "," + linenumber;  // Duplicate; do nothing
	}

	/**
	* Internal method to remove from a subtree.
	* x is the item to remove.
	* t is the node that roots the subtree.
	* Set the new root of the subtree.
	*/
	void remove(const Comparable & x, BinaryNode * & t)
	{
		if (t == NULL)
			return;   // Item not found; do nothing
		if (x < t->element)
			remove(x, t->left);
		else if (t->element < x)
			remove(x, t->right);
		else if (t->left != NULL && t->right != NULL) // Two children
		{
			t->element = findMin(t->right)->element;
			remove(t->element, t->right);
		}
		else
		{
			BinaryNode *oldNode = t;
			t = (t->left != NULL) ? t->left : t->right;
			delete oldNode;
		}
	}

	/**
	* Internal method to find the smallest item in a subtree t.
	* Return node containing the smallest item.
	*/
	BinaryNode * findMin(BinaryNode *t) const
	{
		if (t == NULL)
			return NULL;
		if (t->left == NULL)
			return t;
		return findMin(t->left);
	}

	/**
	* Internal method to find the largest item in a subtree t.
	* Return node containing the largest item.
	*/
	BinaryNode * findMax(BinaryNode *t) const
	{
		if (t != NULL)
			while (t->right != NULL)
				t = t->right;
		return t;
	}

	void findWord(const Comparable & x, BinaryNode *t) ////////////////////////
	{
		while (t != NULL)
			if (x < t->element)
				t = t->left;
			else if (t->element < x)
				t = t->right;
			else {
				cout << "Line numbers<BST>: " << t->linenumber << endl;
				return;    // Match
			}
	}
	/**
	* Internal method to test if an item is in a subtree.
	* x is item to search for.
	* t is the node that roots the subtree.
	*/

	bool contains(const Comparable & x, BinaryNode *t) const
	{
		if (t == NULL)
			return false;
		else if (x < t->element)
			return contains(x, t->left);
		else if (t->element < x)
			return contains(x, t->right);
		else
			return true;    // Match
	}
	/****** NONRECURSIVE VERSION*************************
	bool contains( const Comparable & x, BinaryNode *t ) const
	{
	while( t != NULL )
	if( x < t->element )
	t = t->left;
	else if( t->element < x )
	t = t->right;
	else
	return true;    // Match

	return false;   // No match
	}
	*****************************************************/

	/**
	* Internal method to make subtree empty.
	*/
	void makeEmpty(BinaryNode * & t)
	{
		if (t != NULL)
		{
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		t = NULL;
	}

	/**
	* Internal method to print a subtree rooted at t in sorted order.
	*/
	void printTree(BinaryNode *t, ostream & out) const
	{
		if (t != NULL)
		{
			printTree(t->left, out);
			out << t->element << setw(19 - (t->element.size()) + t->linenumber.size()) << t->linenumber << endl;
			printTree(t->right, out);
		}
	}

	/**
	* Internal method to clone subtree.
	*/
	BinaryNode * clone(BinaryNode *t) const
	{
		if (t == NULL)
			return NULL;
		else
			return new BinaryNode(t->element, clone(t->left), clone(t->right),t->linenumber );
	}

public:

	static int height(BinaryNode* t) {
		// returns the height of the tree t
		if (t == NULL) return 0;
		else {
			int p = height(t->left);
			int q = height(t->right);
			if (p < q)
				return 1 + q;
			else return 1 + p;

		}
	}

	static int size(BinaryNode* t) {
		if (t == NULL) return 0;
		else
			return 1 + size(t->left) + size(t->right);
	}

	BinaryNode* getRoot() {
		return root;
	}

};

#endif