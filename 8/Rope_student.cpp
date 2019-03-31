/*
Write your Rope implementation in this file.
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"
#include <list>

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves
rope_iterator& rope_iterator::operator++() {
	// iterator will keep track of the path of itself from root node
	if (!ptr_->left && !ptr_->right && !ptr_->parent) {
		// corner case: single node tree
		ptr_ = NULL;
		rope_ = NULL;
		path_.clear();
		return *this;
	}

	if (path_[path_.size()-1]->right) {
		// if there's a "right" for the current node, go to that node
		ptr_ = path_[path_.size()-1]->right;
		path_[path_.size()-1] = path_[path_.size()-1]->right; // replace not add

		// going to the leftmost of this "right" path
		while (ptr_->left) {
			path_.push_back(ptr_->left);
			ptr_ = ptr_->left;
		}
	}
	else {
		// there's no "right" for the current node
		if (path_.size() == 1) { // root node
			ptr_ = NULL;
			rope_ = NULL;
			path_.clear();
			return *this;
		}

		if (path_[path_.size()-2]->right == ptr_) {
			// this node is the "right" of its parent, go back up two levels
			if (path_.size() == 2) { // ->parent->parent is the root
				ptr_ = NULL;
				rope_ = NULL;
				path_.clear();
				return *this;
			}

			ptr_ = path_[path_.size()-3];
			path_.pop_back();
			path_.pop_back();
		}
		else {
			// this node is the "left" of its parent, go back up one level
			ptr_ = path_[path_.size()-2];
			path_.pop_back();
		}
	}

	return *this;
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	std::vector<Node*> path;
	if (!root) return iterator(NULL, this, path);

	Node* p = root;

	while (p->left || p->right) { // all the way at the left down to the bottom
		path.push_back(p);
		if (!p->left && p->right) {
			p = p->right; // turn right if right is the only way
		} else {
			p = p->left;
		}
	}
	return iterator(p, this, path);
}

Rope::Rope(){
	size_ = 0;
	root = NULL;
}

void weightTotal(Node* ptr, int& weight) {
	// this fuction calculates the total weights(size) of the rope
	if (ptr->left == NULL && ptr->right == NULL) { // add to sum if it's leaf
		weight += ptr->weight;
		return;
	}
	if (ptr->left) {
		weightTotal(ptr->left, weight);
	}
	if (ptr->right) {
		weightTotal(ptr->right, weight);
	}
}
//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	root = p;
	size_ = 0;
	weightTotal(root, size_);
}

Rope::~Rope(){
	this->destroy_tree(root);
	root = NULL;
}

Rope::Rope(const Rope& r){
	size_ = r.size_;
	root = this->copy_tree(r.root,NULL);
}

Rope& Rope::operator= (const Rope& r){
	if (&r != this) {
		this->destroy_tree(root);
		root = this->copy_tree(r.root,NULL);
		size_ = r.size_;
	}
	return *this;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(const int i, char& c) const{
	if (i > size_-1 || i < 0) {
		std::cerr << "ERROR: Unaddressable access" << '\n';
		return false;
	}

	int ix = 0; // the index of first character of the leaf node's "value"
	Node *tmp = root;
	while(tmp->left || tmp->right) {
		if (tmp->weight + ix > i) { // check weight to determine path
			tmp = tmp->left;
		}
		else {
			ix += tmp->weight;
			tmp = tmp->right;
		}
	}

	c = (tmp->value)[i-ix];
	return true;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r) {
	Node* newRoot = new Node();

	// a copy of Rope r in form of root node instead of Rope needs to be made here.
	// copying Rope r using copy constructor will cause problem because the copy
	// will "destroyed" when this function finishes.
	Node* rhs;
	rhs = copy_tree(r.root, NULL);

	root->parent = newRoot;
	rhs->parent = newRoot;
	newRoot->left = root;
	newRoot->right = rhs;

	root = newRoot;
	newRoot->weight = size_;
	size_ = size_ + r.size_;
}

bool Rope::stringFromIndex(int i, std::string& tempStr) const {
	// this function makes a string starting at i to the end of the string of i's node
	if (i > size_-1 || i < 0)
		return false;

	tempStr.clear();
	int ix = 0;
	Node *tmp = root;
	while(tmp->left || tmp->right) {
		if (tmp->weight + ix > i) {
			tmp = tmp->left;
		}
		else {
			ix += tmp->weight;
			tmp = tmp->right;
		}
	}

	tempStr = (tmp->value).substr(i-ix);
	return true;
}
//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(const int i, const int j, std::string& s) const {
	// some input checks
	if (i>j || j > size_-1 || i < 0) {
		return false;
	}

	s.clear();

	if (i == j) { // if i and j match, just get that one character
		char c;
		if (index(i, c)) {
			s += c;
			return true;
		}
		return false;
	}

	std::string tempStr;

	// this loop will keep adding the strings in nodes where includes "i to j."
	// stringFromIndex function makes sure if i starts in the middle of the string,
	// the extra characters at the front will not be included.
	while(s.length() < j-i+1) {
		if (stringFromIndex(s.length()+i, tempStr)) {
			s += tempStr;
		}
	}

	s = s.substr(0, j-i+1); // cut the extra characters at the end

	if (s.length() > 0)
		return true;
	else
		return false;
}

bool isLeftChild(Node* x) {
	// this function checks if a node is a "left" child node
	if (!x->parent) {
		return false;
	}
	return x == x->parent->left;
}

void disconnect(Node* x) {
	// this function disconnect a node with its parent node
	if (x->parent) {
		if (x->parent->left == x) {
			x->parent->left = NULL;
		} else {
			x->parent->right = NULL;
		}
		x->parent = NULL;
	}
}

void setWeightsAbove(Node* x) {
	// this function use a leaf node to set the weight through the path it goes to
	// the root. The program doesn't have to traverse through all the tree nodes
	// because "break point" nodes are the child nodes for rhs and are on the same
	// path, so going back up from the bottom will set the weights where needed.

	while (x) {

		if (x->left) {
			x->weight = 0;
			weightTotal(x->left, x->weight);
			// std::cout << '\n';
		}

		x = x->parent;
	}
}

void splitNodes(Node* lhs, Node* rhs, const int i, const int ix) {
	if (i == ix) {
		// if spliting at the beginning of the node,
		// node will be completely disconnected and be used for rhs
		Node* t = rhs->parent;
		disconnect(rhs);
		setWeightsAbove(t);
		return;
	}

	if (i == ix + rhs->weight) {
		// rhs is actully on the left part in this corner case
		setWeightsAbove(rhs);
		return;
	}

	lhs = new Node(); // new node for the split node in lhs
	// setting "connections" pointers
	if (rhs->parent) {
		lhs->parent = rhs->parent;

		if (isLeftChild(rhs)) {
			rhs->parent->left = lhs;
		} else {
			rhs->parent->right = lhs;
		}
		rhs->parent = NULL;
	}

	std::string tmpStr = ""; // lhs' string("value" member variable)
	for (size_t j = 0; j < i-ix; j++) {
		tmpStr.push_back((rhs->value)[j]);
	}


	lhs->value = tmpStr;
	lhs->weight = tmpStr.length();
	rhs->value = (rhs->value).substr(i-ix);
	rhs->weight = (rhs->value).length();

	setWeightsAbove(lhs); // some weight has been lost, set the weights correctly
}

Node* concatNodes(Node* x, Node* y) {
	// this function concatenates the broken parts for rhs of the original tree
	if (x == NULL) {
		if (y != NULL) {
			return y;
		}
		return NULL;
	}
	Node* newRoot = new Node();

	newRoot->left = x;
	newRoot->right = y;
	x->parent = newRoot;
	y->parent = newRoot;

	weightTotal(x, newRoot->weight);

	return newRoot;
}

Rope& Rope::splitForSingleNodeTree(const int i, Rope& rhs) {
	// corner case: single node tree
	Node* theNode = new Node();

	theNode->weight = root->weight - i;
	theNode->value = (root->value).substr(i, root->weight);
	rhs.root = theNode;
	rhs.size_ = theNode->weight;

	root->weight = i;
	root->value = (root->value).substr(0, i);
	size_ = i;

	return *this;
}
//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(const int i, Rope& rhs) {
	if (i == size_ || i < 0 || i > size_-1) {
		//                   ^        ^         Rope created will be invalid
		// ^ corner case 1: spilt at the end
		rhs.root = NULL;
		rhs.size_ = 0;

		return *this;
	}
	if (i == 0) {
		// corner case 2: spilt at the beginning
		rhs.root = root;
		rhs.size_ = size_;
		root = NULL;
		size_ = 0;

		return *this;
	}

	if (!root->left && !root->right) {
		this->splitForSingleNodeTree(i, rhs);
		return *this;
	}

	int ix = 0; // this is the index of the current leaf node's string first index
	Node* newRoot = NULL; // this is the root of the second half string split
	Node* tmp = root; // the pointer that will point to index i's node
	std::vector<Node*> bNodes; // where subtrees of rhs form

	while(tmp->left || tmp->right) {
		if (tmp->weight + ix >= i) {
			if (tmp->right) {
				// on the path to the target node, nodes on the right will be for rhs
				bNodes.push_back(tmp->right);
				disconnect(tmp->right);
			}
			tmp = tmp->left;
		}
		else {
			ix += tmp->weight;
			tmp = tmp->right;
		}
	}

	Node* tmp3 = NULL; // this is the split node for lhs
	splitNodes(tmp3, tmp, i, ix);

	// tmp(split node for rhs) will concatenate with all
	// recorded "break points" of the trees
	if (i != ix + tmp->weight) {
		newRoot = tmp;
	}

	for (int j = bNodes.size()-1; j >= 0 ; j--) {
		newRoot = concatNodes(newRoot, bNodes[j]); // make rhs tree
	}

	// set member variables correct
	rhs.root = newRoot;
	rhs.size_ = size_ - i;
	size_ = i;

	return *this;
}
