#pragma once
#include "Passenger.h"

/*
	Josepth类采用单循环链表存储，其工作原理很简单，就是单循环链表的插入与删除，需要注意的地方就是当删除首位结点时的解决方法以及对输入数据的判断检验
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