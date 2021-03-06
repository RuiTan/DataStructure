#pragma once
#include "Passenger.h"
#define MAXAMOUNT 20000

/*
	Josepth类采用单循环链表存储，其工作原理很简单，就是单循环链表的插入与删除，需要注意的地方就是当删除首位结点时的解决方法以及对输入数据的判断检验
*/

class Passenger;
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


Josepth::Josepth() {
	int _amount, _index, _death, _left;
	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K个人为止!\n" << endl;

	cout << "请输入生死游戏的总人数N：\t";
	cin >> _amount;
	setNumbers(_amount, input_type::AMOUNT);

	cout << "请输入游戏开始的位置S：\t\t";
	cin >> _index;
	setNumbers(_index, input_type::FIRSTINDEX);

	cout << "请输入死亡数字M：\t\t";
		cin >> _death;
	setNumbers(_death, input_type::DEATHNUMBER);

	cout << "请输入剩余的生者人数K：\t\t";
	cin >> _left;
	setNumbers(_left, input_type::AMOUNTLEFT);
	cout << endl;

	setJosepthNode(1);
	startKilling(setBeginNode(firstIndex));
	
}
Josepth::~Josepth() {
	head = tail = nullptr;
}
void Josepth::setNumbers(int _input, const int _type) {
	switch (_type) {
	case 0: {
		while (_input < 1 || _input > MAXAMOUNT) {
			cout << "输入的总人数有误，请重新输入：";
			cin >> _input;
		}
		amount = _input;
		break;
	}
	case 1: {
		while (_input < 1 || _input > amount) {
			cout << "输入的开始位置有误，请重新输入：";
			cin >> _input;
		}
		firstIndex = _input;
		break;
	}
	case 2: {
		while (_input <= 1) {
			cout << "输入的死亡数字有误，请重新输入：";
			cin >> _input;
		}
		if (_input > amount) _input = _input % amount;
		deathNumber = _input;
		break;
	}
	case 3: {
		while (_input >= amount || _input <= 0) {
			cout << "输入的剩余人数有误，请重新输入：";
			cin >> _input;
		}
		amountLeft = _input;
		break;
	}
	default: exit(0);
	}
}
Passenger* Josepth::setJosepthNode(int _index) {
	if (_index == amount + 1) return 0;
	if (_index == 1) {
		present = new Passenger(1, NULL);
		head = tail = present;
	}
	else {
		Passenger* _temp = new Passenger(_index, NULL);
		present->next = _temp;
		present = tail = _temp;
		_temp->next = head;
	}
	return setJosepthNode(_index + 1);
}
Passenger* Josepth::setBeginNode(int _index) {
	present = head;
	for (int i = 0; i < amount; i++) {
		if (_index == present->number) {
			return present;
		}
		present = present->next;
	}
}
Passenger* Josepth::deleteNode(Passenger* node) {
	if (node == head){
		tail->next = node->next;
		head = tail->next;
		delete node;
		present = head;
	}
	else if(node == tail){
		Passenger *_node = node->next, *_tail = tail;
		while (true){
			_node = _node->next;
			_tail = _tail->next;
			if (_node == tail){
				tail = _tail;
				break;
			}
		}
		tail->next = node->next;
		delete node;
		present = head;
	}
	else {
		present = node;
		Passenger *_node = node->next, *_present = present;
		while (true) {
			_node = _node->next;
			_present = _present->next;
			if (_node == present) {
				_present->next = node->next;
				present = present->next;
				delete node;
				break;
			}
		}
	}
	return present;
}
void Josepth::startKilling(Passenger* _present) {
	if (amountLeft == amount) {
		cout << "\n最后剩下:\t" << amountLeft << "人" << endl;
		cout << "剩余生者的位置分别是:\n";
		present = head;
		cout << present->number << "\t";
		for (int i = 0; i < amount-1; i++){
			present = present->next;
			cout << present->number << "\t";
		}
		cout << "游戏结束！";
		return;
	}
	else{
		for (int i = 0; i < deathNumber-1; i++){
			_present = _present->next;
		}
		amount--;
		cout << "第" << ++DeathIndex << "个死者的位置是:\t\t" << _present->number << endl;
		_present = deleteNode(_present);
	}
	startKilling(_present);
}