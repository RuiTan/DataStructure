#include "Chessboard.h"
#include <stdio.h>
#include <time.h>

int main() {
	int amount;
	cout << "现有N*N的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一斜线上！\n\n请输入皇后的个数：";
	cin >> amount;
	while (amount <= 0){
		cout << "输入错误，请输入一个正整数：";
		cin >> amount;
	}

	Chessboard chessboard(amount);
	cout << amount << "皇后的摆法共有：" << chessboard.getCount() << "种！\n";
	cout << endl << "这次寻找共用了" << chessboard.getTime() << "s！\n";
	system("pause");
	return 0;
}