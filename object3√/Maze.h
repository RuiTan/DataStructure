#pragma once
#ifndef MAZE_H
#define MAZE_H
#include <iostream>
#include <vector>
#include <fstream>
#include "Node.h"
using namespace std;

/*
	构造的Maze类生成的Maze矩阵采用双向正交链表实现，当然这不是必要的，采用二维链表、二维数组甚至一维链表、一维数组都是可以解决的,但是考虑到当迷宫很大时，正交链表在实现时让那些不是路的节点直接跳过（对应稀疏矩阵），可以很大程度的减少储存空间。
*/
/*
	这里构造的Maze默认入口为左上角（1,1），出口为右下角（line-1，row-1），意即这两个位置必是路，且迷宫外围是一圈“#”构成的墙
*/

class Node;//这里需要声明一下，否则会抛出“Node does not name a type.”错误
class Maze {

public:
	Maze();
	~Maze();
protected:
	Node *findNodeInRow(int, Node*);//在一行中找某节点，若找到返回该节点，否则返回NULL
	void printMaze(ostream &os = cout);//在指定的os输出流中输出Maze，使其默认值为cout
	void printVec(ostream &os = cout);
	void findRoad(bool, bool, bool, bool, Node*);
	void justGo();
private:
	Node *head, *present;
	int row, line;//这里的row和line是行号而不是行数，要注意每行每列都是从0开始，故行号比行数是少一的
	fstream in_file;
	vector<Node*> road_vec;//采用vector来存储当前路过的节点，方便压入和弹出节点
	bool isEnd;
};

Maze::Maze() {
	/*
		由于迷宫是从文件中读取，因此Maze类中数据不需要重载构造函数来初始化，用户要想改变迷宫形状只需要更改in_file.txt文件即可。这里我将Maze类所有的操作函数定义为protected，因为对于用户来说只希望更改迷宫文件就能找到路径，而不需要其他的操作。这些操作函数全部在构造函数内被调用或者是间接调用。
	*/
	head = present = NULL;
	row = line = 0;
	in_file.open("in_file.txt");
	if (!in_file) {
		cout << "文件打开失败！";
		system("pause");
		exit(1);
	}
	in_file >> row >> line;
	//这里的row和line是行号，而不是行数，要注意行号是比行数少1的
	for (int i = 0; i <= row; i++){
		//外侧循环读取列头，内侧循环从相应列头读取行
		Node *_node = new Node();
		in_file >> _node->data;
		_node->y_index = i;
		_node->x_index = 0;
		if (_node->data != '#') _node->is_road = true;
		//如果遇到的不是"#"，则判定为该结点是路，可以添加到Maze正交链表中
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
		}//若是首列头结点，则直接赋值给head，否则要将其与之前的列头结点连在一起
		
		if (i == row)	{
			temp_head1->down = head;
			head->up = temp_head1;
		}//首尾相连，完成首列循环

		for (int j = 1; j <= line; j++){
			//从列头下一个开始存储行
			Node *_node = new Node();
			in_file >> _node->data;
			_node->y_index = i;
			_node->x_index = j;
			if (_node->data != '#') _node->is_road = true;
			if (i != 0 && j != 0) {
				if (!_node->is_road){
					//如果待插入结点不是可走的路，那要判断他是不是行尾，若是，则需要将前一个路结点与行头相连，否则直接跳过
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
				//如果该节点已经插入，也要判断其是否为行尾，同上
				Node *temp_head2 = head;
				for (int k = 1; k <= i; k++) {
					temp_head2 = temp_head2->down;
				}
				present->right = temp_head2;
				temp_head2->left = present;
			}
		}
	}
	//上述操作仅将各行内结点、各行行头结点连在了一起，以下操作将出首列外的每一列连起来
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
		由于Maze采用的是正交链表，因此析构时需要将每个结点空间全部释放，这是一种递归释放，但是这里把递归解开成非递归循环，逐行释放空间知道链表为空。
	*/
	if (head == NULL){
		//空迷宫直接返回，无需析构
		return;
	}
	//非空迷宫需从头结点开始遍历每一个元素，使得所有结点指针均被释放，最后留下头结点，删除之
	Node *temp_head = head, *temp_line = head;
	for (int i = 0; i <= row; i++){
		for (int j = 0; j <= line; j++){
			//这里删除采用和构造时一样的顺序，先找列头，而后从列头往后删除结点，直到所删除结点的right结点是列头，即停止，并删除列头
			if (temp_line->right == head) {
				//此处判断是否到达列尾
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
	//最后释放头结点，Maze为空
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
		os << "这是一个空的迷宫！\n";
		return;
	}
	Node *temp_head = head, *temp_line = head;
	os << "迷宫地图：\n";
	for (int i = 0; i <= line; i++){
		os << "\t" << i << "列";
	}
	os << endl;
	for (int i = 0; i <= row; i++) {
		os << i << "行\t";
		os << temp_head->data << "\t";
		temp_line = temp_head->right;
		for (int j = 1; j <= line; j++) {
			if (temp_line->x_index != j) {
				//判断当前的节点的right节点是否为图形意义上的right，即从其横坐标是否与当前读到的横坐标相等判断，若不等，说明在迷宫图形上该位置应该是一堵墙
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
	}//找到了终点就返回

	if (_present->x_index == 1) _left = false;
	if (_present->x_index == line-1) _right = false;
	if (_present->y_index == 1) _up = false;
	if (_present->y_index == row-1) _down = false;
	//靠边界的结点就不再找边界结点了

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
	}//按照右、下、左、上的顺序搜索下一个路结点，如果没有路了，那同时该结点必然不是终点，则弹出该结点

}
void Maze::justGo() {
	Node *find_begin = head->right->down;
	findRoad(true, true, false, false, find_begin);
	printVec();
}
void Maze::printVec(ostream &os) {
	if (!road_vec.empty()){
		os << "通往胜利的路径是坎坷的：\n";
		vector<Node*>::iterator i_vec = road_vec.begin();
		cout << "(" << (*i_vec)->y_index << "," << (*i_vec)->x_index << ")";
		i_vec++;
		for (; i_vec != road_vec.end(); i_vec++) {
			cout << " -> (" << (*i_vec)->y_index << "," << (*i_vec)->x_index << ")";
		}
	}
	else{
		os << "放弃吧！此迷宫无路可走！\n";
		return;
	}
}
#endif // !MAZE_H


