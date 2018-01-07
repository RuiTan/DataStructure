#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include "Queen.h"
#include <vector>
#include <time.h>
using namespace std;
#define MAXAMOUNT 16

class Chessboard{
public:
	Chessboard();
	~Chessboard();
	Chessboard(int _amount);
	void findQueen(int row);
	void printQueen();
	inline int getCount(){ return count; };
	inline double getTime() { return (double)(time_end - time_begin)/CLOCKS_PER_SEC; };
private:
	vector<Queen*> queen_vec;
	int *present_queen;
	bool *valid_line, *valid_left, *valid_right;
	int queens_amount;
	int count;
	bool if_print;
	clock_t time_begin, time_end;
};

Chessboard::Chessboard(){
	queens_amount = 0;
	present_queen = NULL;
	valid_line = valid_left = valid_right = NULL;
	count = 0;
}

Chessboard::~Chessboard(){
	queens_amount = 0;
	free(present_queen);
	free(valid_left);
	free(valid_right);
	free(valid_line);
	present_queen = NULL;
	valid_line = valid_left = valid_right = NULL;
	count = 0;
}

Chessboard::Chessboard(int _amount):queens_amount(_amount){
	present_queen = (int*) malloc(sizeof(int) * _amount);
	valid_line = (bool*) malloc(sizeof(int) * _amount);
	valid_left = (bool*) malloc(sizeof(int) * 2*_amount-1);
	valid_right = (bool*) malloc(sizeof(int) * 2*_amount-1);
	if (!present_queen || !valid_line || !valid_left || !valid_right) {
		cout << "内存分配失败！" << endl;
		exit(1);
	}
	count = 0;
	for (int i = 0; i < _amount; i++){
		present_queen[i] = 0;
		valid_line[i] = false;
	}
	for (int i = 0; i < 2*_amount-1; i++){
		valid_left[i] = false;
		valid_right[i] = false;
	}
	cout << "是否将所有结果打印出来？（打印结果将会大大降低程序运行速度）y or n：";
	char print;
	cin >> print;
	if_print = false;
	if (print == 'y')
	{
		if_print = true;
	}
	time_begin = clock();
	findQueen(0);
	time_end = clock();
}

void Chessboard::printQueen() {
	vector<Queen*>::iterator i_queen = queen_vec.begin();
	while (i_queen != queen_vec.end()) {
		for (int i = 1; i < (*i_queen)->index_y; i++) {
			cout << "0 ";
		}
		cout << "X ";
		for (int i = 0; i < queens_amount - (*i_queen)->index_y; i++) {
			cout << "0 ";
		}
		cout << endl;
		i_queen++;
	}
	cout << endl;
}

void Chessboard::findQueen(int row){
	//寻找皇后的函数是一个利用编译器自身回溯机制的递归函数，编译器在某次递归结束后会自动返回上一次递归位置，并将结果带回，这种特性与N皇后问题恰好相符合。
	//回溯过程中，如何确定某一位置的皇后是否符合条件是N皇后问题所要解决的最主要的方面，这里采用三个标记数组，对每次添加的皇后更新相应位置的标记，使得下一次选择皇后的位置更具体，降低了暴力搜索的花费。
	for (int i = 0; i < queens_amount; i++){
		if (valid_left[row + i] || valid_right[queens_amount+row-i-1] || valid_line[i]){
			//如果该位置已经被前i-1个皇后标记过，则直接跳到下一个位置查找
			continue;
		}else{
			//否则将其加入可用皇后数组中
			Queen* temp = new Queen(row+1, i+1);
			queen_vec.push_back(temp);
			valid_left[row+i] = valid_right[queens_amount+row-i-1] = valid_line[i] = true;
			//将此时的列、左斜线、右斜线三个位置添加标记
			if (row == queens_amount-1){
				//如果已经找到最后一行，则说明找到了一种摆法，摆法数量加1，并输出之（需要的话）
				count++;
				if (if_print)	printQueen();
			}
			findQueen(row+1);
			//递归对下一行开始查找
			valid_left[row+i] = valid_right[queens_amount+row-i-1] = valid_line[i] = false;
			//回溯时将三个标记取消
			queen_vec.pop_back();
			//将该皇后弹出，以查找下一个皇后
			free(temp);
		}
	}
}

#endif