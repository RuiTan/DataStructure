#pragma once
#include "Passenger.h"

/*
	Josepth类采用单循环链表存储
*/

static enum input_type { AMOUNT, FIRSTINDEX, DEATHNUMBER, AMOUNTLEFT }input_type;//采用enum方便后面判断辨认代码
static int DeathIndex = 0;
class Josepth {
public:
	Josepth();
	~Josepth();
	void setNumbers(int, const int);//设置各类初始数据
	Passenger* setJosepthNode(int);//创建约瑟夫环
	Passenger* setBeginNode(int);//设定游戏开始位置
	Passenger* deleteNode(Passenger*);//删除结点，即杀人
	void startKilling(Passenger*);//开始游戏咯
private:
	Passenger* present;
	Passenger* head;
	Passenger* tail;
	int amount, firstIndex, deathNumber, amountLeft;

};