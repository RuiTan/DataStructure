//
// Created by tanrui on 17-11-9.
//

#pragma once
#include <fstream>

#include <iostream>
#include <sstream>
#include <vector>
using namespace std;
#define PREORDER 0
#define INORDER 1
#define POSTORDER 2
#define LEFT 0
#define RIGHT 1

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


BSortTree::BSortTree() :root(nullptr) {
	createBSortTree();
}
BSortTree::~BSortTree() {
	destroyTree();
}
void BSortTree::createBSortTree() {
	cout << "**\t\t\t\t\t\t 二叉排序树 \t\t\t\t\t\t**\n"
		<< "==========================================================\n"
		<< "**\t\t\t\t\t1 -- 建立二叉排序树\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t2 -- 插入元素\t\t\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t3 -- 查询元素\t\t\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t4 -- 删除元素\t\t\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t5 -- 销毁二叉排序树\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t6 -- 退出程序\t\t\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t7 -- 前序输出二叉树\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t8 -- 中序输出二叉树\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t9 -- 后序输出二叉树\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t10-- 前序非递归输出二叉树\t\t\t\t**\n"
		<< "**\t\t\t\t\t11-- 中序非递归输出二叉树\t\t\t\t**\n"
		<< "**\t\t\t\t\t12-- 后序非递归输出二叉树\t\t\t\t**\n"
		<< "==========================================================\n";
	while (setOperator()) {}
}
bool BSortTree::setOperator() {
	cout << "\n请选择操作(1-12)：";
	int operate = 0;
	cin >> operate;
	switch (operate) {
	case 1: {
		if (!isEmpty()) {
			cout << "当前二叉树不为空，无法创建！";
			break;
		}
		cout << "请输入一串数据来创建二叉树：";
		createTreeFormIn();
		printTree();
		// cout << endl;
		break;
	}
	case 2: {
		cout << "请输入要插入的数据：";
		insertTree();
		// printTree();
		// cout << endl;
		break;
	}
	case 3: {
		if (isEmpty()) {
			cout << "当前二叉树为空，无法搜索！";
			break;
		}
		cout << "请输入要查找的数据：";
		searchTree();
		// printTree();
		// cout << endl;
		break;
	}
	case 4: {
		if (isEmpty()) {
			cout << "当前二叉树为空，无法删除数据！";
			break;
		}
		cout << "请输入要删除的数据：";
		eraseTree();
		// printTree();
		// cout << endl;
		break;
	}
	case 5: {
		if (isEmpty()) {
			cout << "当前二叉树为空，无法销毁！";
			break;
		}
		destroyTree();
		cout << "已删除此次创建的二叉树。\n\n";
		break;
	}
	case 6: {
		exit(1);
	}
	case 7: {
		printTree(PREORDER);
		break;
	}
	case 8: {
		printTree(INORDER);
		break;
	}
	case 9: {
		printTree(POSTORDER);
		break;
	}
	case 10: {
		printTreeNoRecursion(PREORDER);
		break;
	}
	case 11: {
		printTreeNoRecursion(INORDER);
		break;
	}
	case 12: {
		printTreeNoRecursion(POSTORDER);
		break;
	}
	default:
		cout << "输入有误！";
		break;
	}
	return true;
}
void BSortTree::createTreeFormIn() {
	string in_string;
	//    getline(cin, in_string);
	//    getline(cin, in_string);
	ifstream in_file("in_file.txt");
	if (!in_file) {
		cout << "文件打开失败！\n";
		exit(1);
		//		system("pause");
	}
	getline(in_file, in_string);
	istringstream in_stream(in_string);
	int _data;
	while (in_stream >> _data) {
		insertTree(root, _data);
	}
}
bool BSortTree::insertTree() {
	int _data;
	cin >> _data;
	return insertTree(root, _data);
}
bool BSortTree::searchTree() {
	int _data;
	cin >> _data;
	BSortTreeNode *p = searchTree(root, _data);
	if (p == nullptr) {
		cout << "要查找的数据：" << _data << "不在此二叉树中。";
		return false;
	}
	else {
		cout << "已在二叉树中找到" << p->data << "的位置。";
		return true;
	}
}
bool BSortTree::destroyTree() {
	destroyTree(root);
	root = nullptr;
	return true;
}
bool BSortTree::eraseTree() {
	int _data;
	cin >> _data;
	BSortTreeNode *p = searchTree(root, _data);
	if (!p) {
		cout << "要删除的数据不存在于二叉树中。";
		return false;
	}
	else if (p->data == root->data && p->left_child == nullptr && p->right_child == nullptr) {
		delete root;
		root = nullptr;
		return true;
	}
	eraseTree(p);
}
void BSortTree::printTree() {
	if (isEmpty()) {
		cout << "当前二叉树为空，无法打印！";
		return;
	}
	else
		printTreeInOrder(root);
}
void BSortTree::printTree(int op) {
	if (isEmpty()) {
		cout << "当前二叉树为空，无法打印！";
		return;
	}
	else {
		switch (op) {
		case PREORDER: {
			printTreePreOrder(root);
			break;
		}
		case INORDER: {
			printTreeInOrder(root);
			break;
		}
		case POSTORDER: {
			printTreePostOrder(root);
			break;
		}
		default:
			break;
		}
	}
}
void BSortTree::printTreeNoRecursion(int op) {
	if (isEmpty()) {
		cout << "当前二叉树为空，无法打印！";
		return;
	}
	else {
		switch (op) {
		case PREORDER: {
			printTreePreOrderNoRecursion(root);
			break;
		}
		case INORDER: {
			printTreeInOrderNoRecursion(root);
			break;
		}
		case POSTORDER: {
			printTreePostOrderNoRecursion(root);
			break;
		}
		default:
			break;
		}
	}
}
BSortTreeNode* BSortTree::getParent(BSortTreeNode *_current) {
	return (_current == nullptr || _current == root) ? nullptr : getParent(root, _current);
}
bool BSortTree::insertTree(BSortTreeNode *&_current, int _data) {
	if (_current == nullptr) {
		_current = new BSortTreeNode(_data);
		return true;
	}
	if (_current->data > _data)
		return insertTree(_current->left_child, _data);
	else if (_current->data < _data)
		return insertTree(_current->right_child, _data);
	else {
		cout << "数据" << _data << "已存在于二叉排序树中！";
		return false;
	}
}
BSortTreeNode * BSortTree::searchTree(BSortTreeNode *_current, int _data) {
	if (_current == nullptr)	return nullptr;
	else if (_data < _current->data)
		return searchTree(_current->left_child, _data);
	else if (_data > _current->data)
		return searchTree(_current->right_child, _data);
	else
		return _current;
}
bool BSortTree::destroyTree(BSortTreeNode *_current) {
	if (_current != nullptr) {
		destroyTree(_current->left_child);
		destroyTree(_current->right_child);
		delete _current;
		_current = nullptr;
		return true;
	}
	return true;
}
bool BSortTree::eraseTree(BSortTreeNode *&_node) {
	if (_node->left_child == nullptr && _node->right_child == nullptr) {
		if (_node == root) {
			delete root;
			root = nullptr;
		}
		BSortTreeNode *p = getParent(_node);
		if (p->left_child != nullptr && p->left_child->data == _node->data)
			p->left_child = nullptr;
		else if (p->right_child != nullptr && p->right_child->data == _node->data)
			p->right_child = nullptr;
		delete _node;
	}
	else if (_node->left_child == nullptr) {
		getParent(_node)->right_child = _node->right_child;
		delete _node;
	}
	else if (_node->right_child == nullptr) {
		getParent(_node)->left_child = _node->left_child;
		delete _node;
	}
	else {
		BSortTreeNode *p = getFirstNodeInOrder(_node->right_child);
		int temp = p->data;
		eraseTree(p);
		_node->data = temp;
	}
	return true;
}
BSortTreeNode* BSortTree::getFirstNodeInOrder(BSortTreeNode *_current) {
	if (_current->left_child != nullptr)
		return getFirstNodeInOrder(_current->left_child);
	else
		return _current;
}
BSortTreeNode *BSortTree::getParent(BSortTreeNode *_parent, BSortTreeNode *_current) {
	if (_parent->left_child == _current || _parent->right_child == _current) {
		return _parent;
	}
	if (_parent->data > _current->data)
		return getParent(_parent->left_child, _current);
	else if (_parent->data < _current->data)
		return getParent(_parent->right_child, _current);
}
