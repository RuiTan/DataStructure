#include "Josepth.h"


Josepth::Josepth() {
	int _amount, _index, _death, _left;
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ!\n" << endl;

	cout << "������������Ϸ��������N��\t";
	cin >> _amount;
	setNumbers(_amount, input_type::AMOUNT);

	cout << "��������Ϸ��ʼ��λ��S��\t\t";
	cin >> _index;
	setNumbers(_index, input_type::FIRSTINDEX);

	cout << "��������������M��\t\t";
		cin >> _death;
	setNumbers(_death, input_type::DEATHNUMBER);

	cout << "������ʣ�����������K��\t\t";
	cin >> _left;
	setNumbers(_left, input_type::AMOUNTLEFT);
	cout << endl;

	setJosepthNode(1);
	startKilling(setBeginNode(firstIndex));
	
}
Josepth::~Josepth() {}
void Josepth::setNumbers(int _input, const int _type) {
	switch (_type) {
	case 0: {
		while (_input < 1) {
			cout << "������������������������룺";
			cin >> _input;
		}
		amount = _input;
		break;
	}
	case 1: {
		while (_input < 1 && _input > amount) {
			cout << "����Ŀ�ʼλ���������������룺";
			cin >> _input;
		}
		firstIndex = _input;
		break;
	}
	case 2: {
		while (_input <= 1) {
			cout << "��������������������������룺";
			cin >> _input;
		}
		deathNumber = _input;
		break;
	}
	case 3: {
		while (_input >= amount) {
			cout << "�����ʣ�������������������룺";
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
		cout << "\n���ʣ��:\t" << amountLeft << "��" << endl;
		cout << "ʣ�����ߵ�λ�÷ֱ���:\n";
		present = head;
		cout << present->number << "\t";
		for (int i = 0; i < amount-1; i++){
			present = present->next;
			cout << present->number << "\t";
		}
		cout << "\n��Ϸ������(*�����)�������+Enter�˳�";
		return;
	}
	else{
		for (int i = 0; i < deathNumber-1; i++){
			_present = _present->next;
		}
		amount--;
		cout << "��" << ++DeathIndex << "�����ߵ�λ����:\t\t" << _present->number << endl;
		_present = deleteNode(_present);
	}
	startKilling(_present);
}
