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

class Node;//���ﲻ����һ������ġ�Node*�����������ᱨ����֪��Ϊɶqwq
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

#endif // !MAZE_H


