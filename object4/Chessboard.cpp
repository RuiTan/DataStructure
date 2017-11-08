#include "Chessboard.h"

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
	time(&time_begin);
	findQueen(0);
	time(&time_end);
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
	for (int i = 0; i < queens_amount; i++){
		if (valid_left[row + i] || valid_right[queens_amount+row-i-1] || valid_line[i]){
			continue;
		}else{
			Queen* temp = new Queen(row+1, i+1);
			queen_vec.push_back(temp);
			valid_left[row+i] = valid_right[queens_amount+row-i-1] = valid_line[i] = true;
			if (row == queens_amount-1){
				count++;
				if (if_print)	printQueen();
			}
			findQueen(row+1);
			valid_left[row+i] = valid_right[queens_amount+row-i-1] = valid_line[i] = false;
			queen_vec.pop_back();
			free(temp);
		}
	}
}

