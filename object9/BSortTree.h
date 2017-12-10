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
	//用于存储结点数据，同时包含左右子女结点地址信息
	int data;
	BSortTreeNode *left_child, *right_child;
	BSortTreeNode() :data(0), left_child(NULL), right_child(NULL) {}
	BSortTreeNode(int _data, BSortTreeNode *_left = NULL, BSortTreeNode *_right = NULL) :data(_data), left_child(_left), right_child(_right) {}
};
class BSortTree {
	/*
		二叉排序树类，通过获取用户输入的一串数字构建出二叉排序树，其主要特点是某结点数值大于左子女的结点数值而小于右子女的结点数值，中序输出时可实现序列顺序输出
		本项目在项目要求基础上添加了对二叉排序树的删除、销毁、以及非递归前、中、后序遍历的方法，后面会详细讲述算法的操作过程
		本项目较多的使用了内联函数，主要是为了将经常调用的例如遍历、输出等函数声明为内联函数以加快编译速度，实际上对于这样规模很小的项目，内不内联其实是没有必要的
	*/	
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
	/*
		以下函数都是通过调用内部函数完成输出，运用了lambda函数方法，减少了代码行数，否则可能需要额外定义一个函数作为参数，会牺牲代码简洁性以及运行时间
	*/
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
	/*
		非递归遍历二叉树一般都是需要在牺牲空间的条件下换取更快的运行时间，这里的前中后序非递归遍历都会用到辅助栈（实际上是vector容器）
	*/
	inline void PreOrderNoRecursion(BSortTreeNode *_current, void(*visit)(BSortTreeNode *p)) {
		//对于前序遍历来说，访问任意一个结点时都是“一左到底”，同时将访问的结点的右子树根节点放入到辅助栈中（若空则跳过），一左到底结束后便将栈顶设为当前结点，循环采用刚才的操作，直到栈空
		vector<BSortTreeNode *> node_stack;//辅助栈
		BSortTreeNode *temp = _current;
		//temp为当前结点
		while (temp != nullptr) {
			//终止条件：temp为栈顶元素，当栈空temp亦为空，终止循环
			visit(temp);
			//遍历当前结点
			if (temp->right_child != nullptr) {
				node_stack.push_back(temp->right_child);
			}//右结点不为空时将其放到栈中
			if (temp->left_child != nullptr) {
				temp = temp->left_child;
			}
			else if (!node_stack.empty()) {
				temp = *--node_stack.end();
				node_stack.pop_back();
			}
			else {
				temp = nullptr;
			}//一左到底直到当前结点的左子树为空，接下来是否循环则看栈是否为空
		}
	}
	inline void InOrderNoRecursion(BSortTreeNode *_current, void(*visit)(BSortTreeNode *p)) {
		//对于中序遍历来说，由于是先访问左子树，
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
        struct BSortTreeNodeStruct {
            BSortTreeNode *current;
            int tag;

            BSortTreeNodeStruct(BSortTreeNode *p = nullptr) : current(p), tag(LEFT) {};
        };
        BSortTreeNodeStruct node_struct;
        vector<BSortTreeNodeStruct> node_stack;
        BSortTreeNode *temp = _current;
        do {
            while (temp != nullptr) {
                node_struct.current = temp;
                node_struct.tag = LEFT;
                node_stack.push_back(node_struct);
                temp = temp->left_child;
            }
            int ifContinue = 1;
            while (ifContinue && !node_stack.empty()) {
                BSortTreeNodeStruct temp_struct = *--node_stack.end();
                node_stack.pop_back();
                temp = temp_struct.current;
                switch (temp_struct.tag) {
                    case LEFT: {
                        temp_struct.tag = RIGHT;
                        node_stack.push_back(temp_struct);
                        ifContinue = 0;
                        temp = temp->right_child;
                        break;
                    }
                    case RIGHT: {
                        visit(temp);
                        break;
                    }
                }
            }
        } while (!node_stack.empty());
    }
	BSortTreeNode* getFirstNodeInOrder(BSortTreeNode *_current);
	BSortTreeNode* getParent(BSortTreeNode *_parent, BSortTreeNode *_current);
	BSortTreeNode *root;
};


