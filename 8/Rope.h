/*
You may add things to this .h file as needed.
However keep in mind that Rope_provided.cpp will always be compiled in Submitty tests.
So you should not delete or change any methods that are implemented in Rope_provided.cpp
All your implementation should go in Rope_student.cpp
*/

#ifndef _ROPE_H
#define _ROPE_H

#include <string>
#include <vector>
#include <iostream>

class Node{
public:
	Node() : left{NULL}, right{NULL}, parent{NULL}, weight{0} {}
	Node* left;
	Node* right;
	Node* parent;
	int weight;
	std::string value;
};

class Rope;

class rope_iterator{
public:
	rope_iterator();
	rope_iterator(Node* p, const Rope* r, std::vector<Node*> path) : \
		ptr_(p), rope_(r),  path_(path) {}
	rope_iterator(Node* p);
	rope_iterator& operator++();
	rope_iterator operator++(int);
	int weight() const;
	const std::string& value() const;
	std::vector<Node*> getPath() const { return path_; }
	friend class Rope;

	bool operator!=(const rope_iterator& it2) const;
private:
	Node* ptr_;
	const Rope* rope_;
	std::vector<Node*> path_;
};

class Rope{
public:
	Rope();
	~Rope();
	Rope(Node* p);
	Rope(const Rope& old);
	Rope& operator= (const Rope& old);

	typedef rope_iterator iterator;
  friend class rope_iterator;

	bool index(const int i, char& c) const; //Get a single character
	void concat(const Rope& r); //Add the other string to me
	bool report(const int i, const int j, std::string& s) const; //Substring
	Rope& split(const int i, Rope& rhs); //Split the string at index i into this (LHS) and a new Rope rhs

	iterator begin() const;
	iterator end() const;

	int size() const;
	void print(std::ostream& out) const;
	void print_strings(std::ostream& out) const;
	Node* expose_root() const;
	bool stringFromIndex(int i, std::string& tempStr) const;
	Rope& splitForSingleNodeTree(const int i, Rope& rhs);

private:
	void print(std::ostream& out, Node* head, int depth) const;
	void destroy_tree(Node* p) {
		if (!p) return;
		destroy_tree(p->right);
		destroy_tree(p->left);
		delete p;
	}
	Node* copy_tree(Node* old_root, Node* the_parent) {
		if (old_root == NULL)
			return NULL;

		Node *answer = new Node();
		answer->value = old_root->value;
		answer->weight = old_root->weight;
		answer->left = copy_tree(old_root->left, answer);
		answer->right = copy_tree(old_root->right, answer);
		answer->parent = the_parent;

		return answer;
	}
private:
	int size_;
	Node *root;
};

bool is_leaf(Node* p);

void weightTotal(Node* ptr, int& weight);
bool isLeftChild(Node* x);
void disconnect(Node* x);
void setWeightsAbove(Node* x);
void splitNodes(Node* lhs, Node* rhs, const int i, const int ix);
Node* concatNodes(Node* x, Node* y);

#endif
