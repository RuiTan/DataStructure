#include "BSortTree.h"
#include <fstream>

BSortTree::BSortTree() :root(NULL) {
	createBSortTree();
}
BSortTree::~BSortTree() {
	destroyTree();
}
void BSortTree::createBSortTree() {
	cout << "**\t\t\t 二叉排序树 \t\t\t**\n"
		<< "==========================================================\n"
		<< "**\t\t\t1 -- 建立二叉排序树\t\t**\n"
		<< "**\t\t\t2 -- 插入元素\t\t\t**\n"
		<< "**\t\t\t3 -- 查询元素\t\t\t**\n"
		<< "**\t\t\t4 -- 删除元素\t\t\t**\n"
		<< "**\t\t\t5 -- 销毁二叉排序树\t\t**\n"
		<< "**\t\t\t6 -- 退出程序\t\t\t**\n"
		<< "==========================================================\n";
	while (setOperator()) {}
}
bool BSortTree::setOperator() {
	cout << "\n请选择操作(1-5)：";
	int operate = 0;
	cin >> operate;
	switch (operate) {
	case 1: {
		if (!isEmpty()) {
			cout << "当前二叉树不为空，无法创建！";
			break;
		}
		cout << "请输入一串数据来创建二叉树：";
		createTree();
		cout << endl;
		printTree();
		cout << endl;
		break;
	}
	case 2: {
		cout << "请输入要插入的数据：";
		insertTree();
		cout << endl;
		printTree();
		cout << endl;
		break;
	}
	case 3: {
		if (isEmpty()) {
			cout << "当前二叉树为空，无法搜索！";
			break;
		}
		cout << "请输入要查找的数据：";
		searchTree();
		cout << endl;
		printTree();
		cout << endl;
		break;
	}
	case 4:{
		if (isEmpty()) {
			cout << "当前二叉树为空，无法删除数据！";
			break;
		}
		cout << "请输入要删除的数据：";
		eraseTree();
		cout << endl;
		printTree();
		cout << endl;
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
	default:
		cout << "输入有误！";
		break;
	}
	return true;
}
void BSortTree::createTree() {
	string in_string;
	getline(cin, in_string);
	getline(cin, in_string);
/*	ifstream in_file("in_file.txt");
	if (!in_file) {
		cout << "文件打开失败！\n";
		exit(1);
		system("pause");
	}
	getline(in_file, in_string);*/
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
	if (p == NULL) {
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
	root = NULL;
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
	else if (p->data == root->data && p->left_child == NULL && p->right_child == NULL) {
		delete root;
		root = NULL;
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
BSortTreeNode *BSortTree::getParent(BSortTreeNode *_current) {
	return (_current == NULL || _current == root) ? NULL : getParent(root, _current);
}

bool BSortTree::insertTree(BSortTreeNode *&_current, int _data) {
	if (_current == NULL) {
		_current = new BSortTreeNode(_data);
		if (_current == NULL) {
			cerr << "内存不足，创建失败！\n";
			exit(1);
			system("pause");
		}
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
	if (_current == NULL)	return NULL;
	else if (_data < _current->data)
		return searchTree(_current->left_child, _data);
	else if (_data > _current->data)
		return searchTree(_current->right_child, _data);
	else
		return _current;
}
bool BSortTree::destroyTree(BSortTreeNode *_current) {
	if (_current != NULL) {
		destroyTree(_current->left_child);
		destroyTree(_current->right_child);
		delete _current;
		_current = NULL;
		return true;
	}
	return true;
}
bool BSortTree::eraseTree(BSortTreeNode *&_node) {
	if (_node->left_child == NULL && _node->right_child == NULL) {
		if (_node == root) {
			delete root;
			root == NULL;
		}
		BSortTreeNode *p = getParent(_node);
		if (p->left_child != NULL && p->left_child->data == _node->data)
			p->left_child = NULL;
		else if (p->right_child != NULL && p->right_child->data == _node->data)
			p->right_child = NULL;
		delete _node;
	}
	else if (_node->left_child == NULL) {
		getParent(_node)->right_child = _node->right_child;
		delete _node;
	}
	else if (_node->right_child == NULL) {
		getParent(_node)->left_child = _node->left_child;
		delete _node;
	}
	else {
		BSortTreeNode *p = getFisrtNodeInOrder(_node->right_child);
		int temp = p->data;
		eraseTree(p);
		_node->data = temp;
	}
	return true;
}
void BSortTree::printTreeInOrder(BSortTreeNode *_current) {
	if (_current != NULL) {
		printTreeInOrder(_current->left_child);
		cout << _current->data << "->";
		printTreeInOrder(_current->right_child);
	}
}
BSortTreeNode *BSortTree::getFisrtNodeInOrder(BSortTreeNode *_current) {
	if (_current->left_child != NULL)
		return getFisrtNodeInOrder(_current->left_child);
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