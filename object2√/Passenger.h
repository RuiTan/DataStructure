#pragma once

#include <iostream>
using namespace std;

/*
	Passenger类用来存储旅客，主要数据是该旅客的位置编号及指向下一个旅客的指针
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

