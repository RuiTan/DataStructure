#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <iostream>
#include "Queen.h"
#include <vector>
#include <time.h>
using namespace std;

class Chessboard{
public:
	Chessboard();
	~Chessboard();
	Chessboard(int _amount);
	void findQueen(int row);
	void printQueen();
	inline int getCount(){ return count; };
	inline time_t getTime() { return time_end - time_begin; };
private:
	vector<Queen*> queen_vec;
	int *present_queen;
	bool *valid_line, *valid_left, *valid_right;
	int queens_amount;
	int count;
	bool if_print;
	time_t time_begin, time_end;
};


#endif