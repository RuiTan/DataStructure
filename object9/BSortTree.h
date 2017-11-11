//
// Created by tanrui on 17-11-9.
//

#pragma once

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#define PREORDER 0
#define INORDER 1
#define POSTORDER 2

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
	inline bool isEmpty() { return root == NULL ? true : false; }
	void createBSortTree();
	bool setOperator();
	void createTreeFormIn();
	bool insertTree();
	bool searchTree();
	bool destroyTree();
	bool eraseTree();
	void printTree();
	void printTree(int op);
	void printTreeNoRecursion(int op);
	inline void printTreeInOrder(BSortTreeNode *_current) {
		InOrder(_current, [](BSortTreeNode *p) {
			cout << p->data << "->";
		});
	};
	inline void printTreePreOrder(BSortTreeNode *_current) {
		PreOrder(_current, [](BSortTreeNode *p) {
			cout << p->data << "->";
		});
	};
	inline void printTreePostOrder(BSortTreeNode *_current) {
		PostOrder(_current, [](BSortTreeNode *p) {
			cout << p->data << "->";
		});
	};
	inline void printTreeInOrderNoRecursion(BSortTreeNode *_current) {
		InOrderNoRecursion(_current, [](BSortTreeNode *p) {
			cout << p->data << "->";
		});
	}
	inline void printTreePreOrderNoRecursion(BSortTreeNode *_current) {
		PreOrderNoRecursion(_current, [](BSortTreeNode *p) {
			cout << p->data << "->";
		});
	}
	inline void printTreePostOrderNoRecursion(BSortTreeNode *_current) {
		PostOrderNoRecursion(_current, [](BSortTreeNode *p) {
			cout << p->data << "->";
		});
	}
	BSortTreeNode *getParent(BSortTreeNode *_current);
protected:
	bool insertTree(BSortTreeNode *&_current, int _data);
	BSortTreeNode *searchTree(BSortTreeNode *_current, int _data);
	bool destroyTree(BSortTreeNode *_current);
	bool eraseTree(BSortTreeNode *&_current);
	inline void InOrder(BSortTreeNode *_current, void(*visit)(BSortTreeNode *p)) {
		if (_current != NULL) {
			InOrder(_current->left_child, visit);
			visit(_current);
			InOrder(_current->right_child, visit);
		}
	};
	inline void PreOrder(BSortTreeNode *_current, void(*visit)(BSortTreeNode *p)) {
		if (_current != NULL) {
			visit(_current);
			PreOrder(_current->left_child, visit);
			PreOrder(_current->right_child, visit);
		}
	};
	inline void PostOrder(BSortTreeNode *_current, void(*visit)(BSortTreeNode *p)) {
		if (_current != NULL) {
			PostOrder(_current->left_child, visit);
			PostOrder(_current->right_child, visit);
			visit(_current);
		}
	};
	inline void PreOrderNoRecursion(BSortTreeNode *_current, void(*visit)(BSortTreeNode *p)) {
		vector<BSortTreeNode *> node_stack;
		BSortTreeNode *temp = _current;
		while (temp != nullptr) {
			visit(temp);
			if (temp->right_child != nullptr) {
				node_stack.push_back(temp->right_child);
			}
			if (temp->left_child != nullptr) {
				temp = temp->left_child;
			}
			else if (!node_stack.empty()) {
				temp = *--node_stack.end();
				node_stack.pop_back();
			}
			else {
				temp = nullptr;
			}
		}
	}
	inline void InOrderNoRecursion(BSortTreeNode *_current, void(*visit)(BSortTreeNode *p)) {
		vector<BSortTreeNode *> node_stack;
		BSortTreeNode *temp = _current;
		node_stack.push_back(temp);
		do {
			if (temp == nullptr && !node_stack.empty()) {
				temp = *--node_stack.end();
				if (temp->right_child != nullptr) {
					BSortTreeNode *p = temp->right_child;
					visit(temp);
					node_stack.pop_back();
					temp = p;
					node_stack.push_back(temp);
					p = nullptr;
				}
				else {
					visit(temp);
					node_stack.pop_back();
					temp = nullptr;
				}
			}
			else{
				while (temp->left_child != nullptr) {
					temp = temp->left_child;
					node_stack.push_back(temp);
				}
				temp = nullptr;
			}
			
		} while (temp != nullptr || !node_stack.empty());
	}
	inline void PostOrderNoRecursion(BSortTreeNode *_current, void(*visit)(BSortTreeNode *p)) {
		
	}
	BSortTreeNode* getFirstNodeInOrder(BSortTreeNode *_current);
	BSortTreeNode* getParent(BSortTreeNode *_parent, BSortTreeNode *_current);
	BSortTreeNode *root;
};