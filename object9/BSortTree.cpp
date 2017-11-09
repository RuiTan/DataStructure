//
// Created by tanrui on 17-11-9.
//

#include "BSortTree.h"
#include <fstream>

BSortTree::BSortTree() :root(nullptr) {
	createBSortTree();
}
BSortTree::~BSortTree() {
	destroyTree();
}
void BSortTree::createBSortTree() {
	cout << "**\t\t\t\t\t\t ���������� \t\t\t\t\t\t**\n"
		<< "==========================================================\n"
		<< "**\t\t\t\t\t1 -- ��������������\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t2 -- ����Ԫ��\t\t\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t3 -- ��ѯԪ��\t\t\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t4 -- ɾ��Ԫ��\t\t\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t5 -- ���ٶ���������\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t6 -- �˳�����\t\t\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t7 -- ǰ�����������\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t8 -- �������������\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t9 -- �������������\t\t\t\t\t**\n"
		<< "**\t\t\t\t\t10-- ǰ��ǵݹ����������\t\t\t\t**\n"
		<< "**\t\t\t\t\t11-- ����ǵݹ����������\t\t\t\t**\n"
		<< "**\t\t\t\t\t12-- ����ǵݹ����������\t\t\t\t**\n"
		<< "==========================================================\n";
	while (setOperator()) {}
}
bool BSortTree::setOperator() {
	cout << "\n��ѡ�����(1-12)��";
	int operate = 0;
	cin >> operate;
	switch (operate) {
	case 1: {
		if (!isEmpty()) {
			cout << "��ǰ��������Ϊ�գ��޷�������";
			break;
		}
		cout << "������һ��������������������";
		createTreeFormIn();
		cout << endl;
		printTree();
		cout << endl;
		break;
	}
	case 2: {
		cout << "������Ҫ��������ݣ�";
		insertTree();
		cout << endl;
		printTree();
		cout << endl;
		break;
	}
	case 3: {
		if (isEmpty()) {
			cout << "��ǰ������Ϊ�գ��޷�������";
			break;
		}
		cout << "������Ҫ���ҵ����ݣ�";
		searchTree();
		cout << endl;
		printTree();
		cout << endl;
		break;
	}
	case 4: {
		if (isEmpty()) {
			cout << "��ǰ������Ϊ�գ��޷�ɾ�����ݣ�";
			break;
		}
		cout << "������Ҫɾ�������ݣ�";
		eraseTree();
		cout << endl;
		printTree();
		cout << endl;
		break;
	}
	case 5: {
		if (isEmpty()) {
			cout << "��ǰ������Ϊ�գ��޷����٣�";
			break;
		}
		destroyTree();
		cout << "��ɾ���˴δ����Ķ�������\n\n";
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
		cout << "��������";
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
		cout << "�ļ���ʧ�ܣ�\n";
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
		cout << "Ҫ���ҵ����ݣ�" << _data << "���ڴ˶������С�";
		return false;
	}
	else {
		cout << "���ڶ��������ҵ�" << p->data << "��λ�á�";
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
		cout << "Ҫɾ�������ݲ������ڶ������С�";
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
		cout << "��ǰ������Ϊ�գ��޷���ӡ��";
		return;
	}
	else
		printTreeInOrder(root);
}
void BSortTree::printTree(int op) {
	if (isEmpty()) {
		cout << "��ǰ������Ϊ�գ��޷���ӡ��";
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
		cout << "��ǰ������Ϊ�գ��޷���ӡ��";
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
		cout << "����" << _data << "�Ѵ����ڶ����������У�";
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