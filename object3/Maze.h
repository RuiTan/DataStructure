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

class Node;//这里不声明一下下面的“Node*”声明变量会报错，不知道为啥qwq
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

#endif // !MAZE_H


