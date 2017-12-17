#pragma once

#include <iostream>
using namespace std;

/*
	Passenger�������洢�ÿͣ���Ҫ�����Ǹ��ÿ͵�λ�ñ�ż�ָ����һ���ÿ͵�ָ��
*/

class Passenger {
	friend class Josepth;
public:
	Passenger();
	Passenger(int, Passenger*);
	~Passenger();
private:
	int number;
	Passenger* next;
};
Passenger::Passenger() {
	number = 0;
	next = NULL;
}

Passenger::Passenger(int _number, Passenger* _next) :number(_number), next(_next) {
}

Passenger::~Passenger() {
	number = 0;
	next = NULL;
}

