#include "Chessboard.h"
#include <stdio.h>
#include <time.h>

int main() {
	int amount;
	cout << "����N*N�����̣�����N���ʺ�Ҫ�����лʺ���ͬһ�С��к�ͬһб���ϣ�\n\n������ʺ�ĸ�����";
	cin >> amount;
	while (amount <= 0){
		cout << "�������������һ����������";
		cin >> amount;
	}

	Chessboard chessboard(amount);
	cout << amount << "�ʺ�İڷ����У�" << chessboard.getCount() << "�֣�\n";
	cout << endl << "���Ѱ�ҹ�����" << chessboard.getTime() << "s��\n";
	system("pause");
	return 0;
}