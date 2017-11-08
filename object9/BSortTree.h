#pragma once
#include <iostream>
#include <sstream>
using namespace std;

struct BSortTreeNode {
	int data;
	BSortTreeNode *left_child, *right_child;
	BSortTreeNode() :data(0), left_child(NULL), right_child(NULL) {}
	BSortTreeNode(int _data, BSortTreeNode *_left = NULL, BSortTreeNode *_right = NULL) :data(_data), left_child(_left), right_child(_right) {}
};

class BSortTree {
public:
	BSortTree();
	~BSortTree();
	bool isEmpty() { return root == NULL ? true : false; }
	void createBSortTree();
	bool setOperator();
	void createTree();
	bool insertTree();
	bool searchTree();
	bool destroyTree();
	bool eraseTree();
	void printTree();
	BSortTreeNode *getParent(BSortTreeNode *_current);
protected:
	bool insertTree(BSortTreeNode *&_current, int _data);
	BSortTreeNode *searchTree(BSortTreeNode *_current, int _data);
	bool destroyTree(BSortTreeNode *_current);
	bool eraseTree(BSortTreeNode *&_current);
	void printTreeInOrder(BSortTreeNode *_current);
	BSortTreeNode *getFisrtNodeInOrder(BSortTreeNode *_current);
	BSortTreeNode *getParent(BSortTreeNode *_parent, BSortTreeNode *_current);
	BSortTreeNode *root;
};