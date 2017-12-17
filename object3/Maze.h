#pragma once
#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <vector>
#include <fstream>
#include "Node.h"
using namespace std;

/*
	�����Maze�����ɵ�Maze�������˫����������ʵ�֣���Ȼ�ⲻ�Ǳ�Ҫ�ģ����ö�ά������ά��������һά����һά���鶼�ǿ��Խ����,���ǿ��ǵ����Թ��ܴ�ʱ������������ʵ��ʱ����Щ����·�Ľڵ�ֱ����������Ӧϡ����󣩣����Ժܴ�̶ȵļ��ٴ���ռ䡣
*/
/*
	���ﹹ���MazeĬ�����Ϊ���Ͻǣ�1,1��������Ϊ���½ǣ�line-1��row-1�����⼴������λ�ñ���·�����Թ���Χ��һȦ��#�����ɵ�ǽ
*/

class Node;//������Ҫ����һ�£�������׳���Node does not name a type.������
class Maze {

public:
	Maze();
	~Maze();
protected:
	Node *findNodeInRow(int, Node*);//��һ������ĳ�ڵ㣬���ҵ����ظýڵ㣬���򷵻�NULL
	void printMaze(ostream &os = cout);//��ָ����os����������Maze��ʹ��Ĭ��ֵΪcout
	void printVec(ostream &os = cout);
	void findRoad(bool, bool, bool, bool, Node*);
	void justGo();
private:
	Node *head, *present;
	int row, line;//�����row��line���кŶ�����������Ҫע��ÿ��ÿ�ж��Ǵ�0��ʼ�����кű���������һ��
	fstream in_file;
	vector<Node*> road_vec;//����vector���洢��ǰ·���Ľڵ㣬����ѹ��͵����ڵ�
	bool isEnd;
};

Maze::Maze() {
	/*
		�����Թ��Ǵ��ļ��ж�ȡ�����Maze�������ݲ���Ҫ���ع��캯������ʼ�����û�Ҫ��ı��Թ���״ֻ��Ҫ����in_file.txt�ļ����ɡ������ҽ�Maze�����еĲ�����������Ϊprotected����Ϊ�����û���˵ֻϣ�������Թ��ļ������ҵ�·����������Ҫ�����Ĳ�������Щ��������ȫ���ڹ��캯���ڱ����û����Ǽ�ӵ��á�
	*/
	head = present = NULL;
	row = line = 0;
	in_file.open("in_file.txt");
	if (!in_file) {
		cout << "�ļ���ʧ�ܣ�";
		system("pause");
		exit(1);
	}
	in_file >> row >> line;
	//�����row��line���кţ�������������Ҫע���к��Ǳ�������1��
	for (int i = 0; i <= row; i++){
		//���ѭ����ȡ��ͷ���ڲ�ѭ������Ӧ��ͷ��ȡ��
		Node *_node = new Node();
		in_file >> _node->data;
		_node->y_index = i;
		_node->x_index = 0;
		if (_node->data != '#') _node->is_road = true;
		//��������Ĳ���"#"�����ж�Ϊ�ý����·��������ӵ�Maze����������
		present = _node;

		Node *temp_head1 = head;
		if (i == 0) head = _node;
		else {
			temp_head1 = _node;
			Node *temp_head2 = head;
			for (int k = 1; k < i; k++){
				temp_head2 = temp_head2->down;
			}
			temp_head2->down = temp_head1;
			temp_head1->up = temp_head2;
		}//��������ͷ��㣬��ֱ�Ӹ�ֵ��head������Ҫ������֮ǰ����ͷ�������һ��
		
		if (i == row)	{
			temp_head1->down = head;
			head->up = temp_head1;
		}//��β�������������ѭ��

		for (int j = 1; j <= line; j++){
			//����ͷ��һ����ʼ�洢��
			Node *_node = new Node();
			in_file >> _node->data;
			_node->y_index = i;
			_node->x_index = j;
			if (_node->data != '#') _node->is_road = true;
			if (i != 0 && j != 0) {
				if (!_node->is_road){
					//����������㲻�ǿ��ߵ�·����Ҫ�ж����ǲ�����β�����ǣ�����Ҫ��ǰһ��·�������ͷ����������ֱ������
					if (j == line) {
						Node *temp_head2 = head;
						for (int k = 1; k <= i; k++) {
							temp_head2 = temp_head2->down;
						}
						present->right = temp_head2;
						temp_head2->left = present;
					}
					continue;
				}
			}
			_node->left = present;
			present->right = _node;
			present = _node;
			if (j == line) {
				//����ýڵ��Ѿ����룬ҲҪ�ж����Ƿ�Ϊ��β��ͬ��
				Node *temp_head2 = head;
				for (int k = 1; k <= i; k++) {
					temp_head2 = temp_head2->down;
				}
				present->right = temp_head2;
				temp_head2->left = present;
			}
		}
	}
	//�����������������ڽ�㡢������ͷ���������һ�����²��������������ÿһ��������
	Node *temp_head, *temp_line1 = head;
	for (int i = 1; i <= line; i++){
		temp_head = head;
		temp_line1 = temp_line1->right;
		Node *temp_line2 = temp_line1;
		for (int j = 1; j <= row+1; j++){
			temp_head = temp_head->down;
			Node *find_node = findNodeInRow(i, temp_head);
			if (j == row + 1) {
				temp_line2->down = temp_line1;
				temp_line1->up = temp_line2;
				continue;
			}
			if (find_node != NULL) {
				temp_line2->down = find_node;
				find_node->up = temp_line2;
				temp_line2 = find_node;
			}
		}
	}

	printMaze();
	justGo();
}
Maze::~Maze(){
	/*
		����Maze���õ������������������ʱ��Ҫ��ÿ�����ռ�ȫ���ͷţ�����һ�ֵݹ��ͷţ���������ѵݹ�⿪�ɷǵݹ�ѭ���������ͷſռ�֪������Ϊ�ա�
	*/
	if (head == NULL){
		//���Թ�ֱ�ӷ��أ���������
		return;
	}
	//�ǿ��Թ����ͷ��㿪ʼ����ÿһ��Ԫ�أ�ʹ�����н��ָ������ͷţ��������ͷ��㣬ɾ��֮
	Node *temp_head = head, *temp_line = head;
	for (int i = 0; i <= row; i++){
		for (int j = 0; j <= line; j++){
			//����ɾ�����ú͹���ʱһ����˳��������ͷ���������ͷ����ɾ����㣬ֱ����ɾ������right�������ͷ����ֹͣ����ɾ����ͷ
			if (temp_line->right == head) {
				//�˴��ж��Ƿ񵽴���β
				delete temp_line;
				if (head->data != '#'){
					break;
				}
				temp_head = head;
				head = head->down;
				delete temp_head;
				j = line + 1;
			}
			else{
				temp_head = temp_head->right;
				temp_line = temp_head->right;
				if (temp_head == temp_line){
					break;
				}
				delete temp_head;
				temp_head = temp_line;
				if (temp_line == head) {
					temp_head = head;
					head = head->down;
					delete temp_head;
					j = line + 1;
				}
			}
		}
		temp_head = head;
	}
	head = NULL;
	//����ͷ�ͷ��㣬MazeΪ��
}
Node *Maze::findNodeInRow(int index, Node* _head) {
	Node* _temp_head = _head;
	while (true) {
		_temp_head = _temp_head->right;
		if (_temp_head->x_index == index) {
			return _temp_head;
		}
		if (_temp_head == _head) {
			return NULL;
		}
	}
	return NULL;
}
void Maze::printMaze(ostream &os) {
	if (head == NULL){
		os << "����һ���յ��Թ���\n";
		return;
	}
	Node *temp_head = head, *temp_line = head;
	os << "�Թ���ͼ��\n";
	for (int i = 0; i <= line; i++){
		os << "\t" << i << "��";
	}
	os << endl;
	for (int i = 0; i <= row; i++) {
		os << i << "��\t";
		os << temp_head->data << "\t";
		temp_line = temp_head->right;
		for (int j = 1; j <= line; j++) {
			if (temp_line->x_index != j) {
				//�жϵ�ǰ�Ľڵ��right�ڵ��Ƿ�Ϊͼ�������ϵ�right��������������Ƿ��뵱ǰ�����ĺ���������жϣ������ȣ�˵�����Թ�ͼ���ϸ�λ��Ӧ����һ��ǽ
				os << "#\t";
				continue;
			}
			os << temp_line->data << "\t";
			temp_line = temp_line->right;
		}
		os << endl << endl;
		temp_head = temp_head->down;
	}
}
void Maze::findRoad(bool _right, bool _down, bool _left, bool _up, Node *_present) {
	road_vec.push_back(_present);
	if (_present->x_index == line - 1 && _present->y_index == row - 1) {
		isEnd = true;
		return;
	}//�ҵ����յ�ͷ���

	if (_present->x_index == 1) _left = false;
	if (_present->x_index == line-1) _right = false;
	if (_present->y_index == 1) _up = false;
	if (_present->y_index == row-1) _down = false;
	//���߽�Ľ��Ͳ����ұ߽�����

	if (_right && _present->right->x_index == _present->x_index+1 && !isEnd) {
		findRoad(true, true, false, true, _present->right);
	}
	if (_down && _present->down->y_index == _present->y_index+1 && !isEnd){
		findRoad(true, true, true, false, _present->down);
	}
	if (_left && _present->left->x_index == _present->x_index - 1 && !isEnd) {
		findRoad(false, true, true, true, _present->left);
	}
	if (_up && _present->up->y_index == _present->y_index - 1 && !isEnd) {
		findRoad(true, false, true, true, _present->up);
	}
	if (!isEnd) {
		road_vec.pop_back();
	}//�����ҡ��¡����ϵ�˳��������һ��·��㣬���û��·�ˣ���ͬʱ�ý���Ȼ�����յ㣬�򵯳��ý��

}
void Maze::justGo() {
	Node *find_begin = head->right->down;
	findRoad(true, true, false, false, find_begin);
	printVec();
}
void Maze::printVec(ostream &os) {
	if (!road_vec.empty()){
		os << "ͨ��ʤ����·���ǿ����ģ�\n";
		vector<Node*>::iterator i_vec = road_vec.begin();
		cout << "(" << (*i_vec)->y_index << "," << (*i_vec)->x_index << ")";
		i_vec++;
		for (; i_vec != road_vec.end(); i_vec++) {
			cout << " -> (" << (*i_vec)->y_index << "," << (*i_vec)->x_index << ")";
		}
	}
	else{
		os << "�����ɣ����Թ���·���ߣ�\n";
		return;
	}
}
#endif // !MAZE_H


