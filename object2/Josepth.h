#pragma once
#include "Passenger.h"

/*
	Josepth����õ�ѭ������洢
*/

static enum input_type { AMOUNT, FIRSTINDEX, DEATHNUMBER, AMOUNTLEFT }input_type;//����enum��������жϱ��ϴ���
static int DeathIndex = 0;
class Josepth {
public:
	Josepth();
	~Josepth();
	void setNumbers(int, const int);//���ø����ʼ����
	Passenger* setJosepthNode(int);//����Լɪ��
	Passenger* setBeginNode(int);//�趨��Ϸ��ʼλ��
	Passenger* deleteNode(Passenger*);//ɾ����㣬��ɱ��
	void startKilling(Passenger*);//��ʼ��Ϸ��
private:
	Passenger* present;
	Passenger* head;
	Passenger* tail;
	int amount, firstIndex, deathNumber, amountLeft;

};