#include "ExamineeList.h"

ExamineeList::ExamineeList(istream &in){
	head_examinee = examinee =  NULL;

	cout << "�����뽨��������Ϣϵͳ��\n�����뿼��������";
	cin >> ExamineeAmount;
	do {
		if (ExamineeAmount > MAXAMOUNT || ExamineeAmount < 0) {
			cout << "����Ŀ�������������Ҫ�����������룺";
			cin >> ExamineeAmount;
		}
		else break;
	} while(true);

	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	for (int i = 0; i < ExamineeAmount; i++) {
		int _num, _age;
		string _name, _type, _sex;
		bool bool_sex = false;
		in >> _num >> _name >> _sex >> _age >> _type;
		while (ifNumExist(_num)) {
			cout << "����" << _num << "�Ѵ��ڣ�����������ÿ����Ŀ��ţ��������Ա����估�������" << endl;
			cin >> _num >> _name >> _sex >> _age >> _type;
		} ;
		num_vec.push_back(_num);
		if (_sex == "��") { bool_sex = true; }
		Examinee* _examinee = new Examinee(_num, _name, bool_sex, _age, _type);
		if (head_examinee == NULL){
			head_examinee = examinee = _examinee;
		}
		else {
			examinee->setNextExaminee(*_examinee);
			_examinee->setPrevExaminee(*examinee);
			examinee = _examinee;
		}
	}
	tail_examinee = examinee;
	printList();
	getchar();
}
ExamineeList::~ExamineeList() {
	for (int i = 0; i < ExamineeAmount; i++)
	{
		deleteExaminee(1);
	}
}
bool ExamineeList::ifNumExist(int num) {
	return binary_search(num_vec.begin(), num_vec.end(), num);
}
void ExamineeList::printList() {
	cout << "\n*************��������ϵͳ���*************";
	if (ExamineeAmount == 0){
		cout << "*****��������ϵͳ����ʱû�п�����Ϣ��*****\n";
	}
	else {
		cout << "\n����\t����\t�Ա�\t����\t��������\n";
		cout << *head_examinee << endl;
		Examinee* _examinee = head_examinee;
		for (int i = 1; i < ExamineeAmount; i++) {
			cout << *_examinee->getNextExaminee() << endl;
			_examinee = _examinee->getNextExaminee();
		}
	}
	cout << "******************************************" << endl;
	cout << "\n��ѡ����Ҫ���еĲ�������1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	int op;
	cin >> op;
	operateList(op);
}
void ExamineeList::operateList(int op) {
	switch (op)
	{
	case 0: exit(0);
	case 1: {
		insertExaminee();
		break;
	};
	case 2: {
		cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
		int num;
		cin >> num;
		deleteExaminee(num);
		break;
	};
	case 3: {
		cout << "������Ҫ���ҵĿ����Ŀ��ţ�";
		int num;
		cin >> num;
		searchExaminee(num);
		break;
	};
	case 4: {
		cout << "������Ҫ�޸ĵĿ����Ŀ��ţ�";
		int num;
		cin >> num;
		modificationExaminee(num);
		break;
	};
	case 5: {
		cout << "������Ҫͳ�Ƶ���Ϣ��1Ϊ������2Ϊ�Ա�3Ϊ���䣬4Ϊ�������ͣ���";
		int info;
		cin >> info;
		countExaminee(info);
		break;
	}
	default: {
		cout << "������������������ѡ����Ҫ���еĲ�������1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
		int op;
		cin >> op;
		operateList(op);
	};
	};
	printList();
	cout << "\n��ѡ����Ҫ���еĲ�������1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	cin >> op;
	operateList(op);
}
void ExamineeList::insertExaminee() {
	cout << "��ѡ����Ҫ����Ŀ���λ��(��ǰ���п���" << ExamineeAmount << "��)��";
	int index;
	cin >> index;
	while (index < 0) {
		cout << "������Ŀ���λ���������������룺";
		cin >> index;
	};
	cout << "����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
	int _num, _age;
	string _name, _type, _sex;
	bool bool_sex = false;
	cin >> _num >> _name >> _sex >> _age >> _type;
	if (binary_search(num_vec.begin(), num_vec.end(), _num)){
		cout << "����Ϊ" << _num << "�Ŀ����Ѵ��ڣ�����������Ҫ����Ŀ����Ŀ��ţ��������Ա����估�������" << endl;
		cin >> _num >> _name >> _sex >> _age >> _type;
	}
	num_vec.push_back(_num);
	if (_sex == "��") { bool_sex = true; }
	Examinee *p_exa = new Examinee(_num, _name, bool_sex, _age, _type);
	if (index > ExamineeAmount) {
		p_exa->setPrevExaminee(*tail_examinee);
		tail_examinee->setNextExaminee(*p_exa);
		tail_examinee = p_exa;
	}
	else  if (index == 1) {
		p_exa->setNextExaminee(*head_examinee);
		head_examinee->setPrevExaminee(*p_exa);
		head_examinee = p_exa;
	}
	else {
		Examinee* temp_exa = head_examinee;
		for (int i = 0; i < index - 2; i++) {
			temp_exa = temp_exa->getNextExaminee();
		}
		temp_exa->getNextExaminee()->setPrevExaminee(*p_exa);
		p_exa->setNextExaminee(*temp_exa->getNextExaminee());
		temp_exa->setNextExaminee(*p_exa);
		p_exa->setPrevExaminee(*temp_exa);
	}
	ExamineeAmount += 1;
}
void ExamineeList::deleteExaminee(int num) {
	Examinee* _examinee = head_examinee;
	bool deleted = false;
	for (int i = 0; i < ExamineeAmount; i++){
		if (_examinee->getExam_num() == num){
			deleted = true;
			if (_examinee == head_examinee){
				head_examinee = head_examinee->getNextExaminee();
				head_examinee->noPrevExaminee();
				_examinee->noNextExaminee();
			}
			else if (_examinee == tail_examinee) {
				tail_examinee = tail_examinee->getPrevExaminee();
				tail_examinee->noNextExaminee();
				_examinee->noPrevExaminee();
			}
			else {
				_examinee->getNextExaminee()->setPrevExaminee(*_examinee->getPrevExaminee());
				_examinee->getPrevExaminee()->setNextExaminee(*_examinee->getNextExaminee());
			}
			cout << "����Ҫɾ���Ŀ�����ϢΪ��" << *_examinee << endl;
			delete _examinee;
			ExamineeAmount -= 1;
			vector<int>::iterator in = num_vec.begin();
			for (; in < num_vec.end(); in++) {
				if (*in == num) {
					num_vec.erase(in);
					break;
				}
			}
			break;
		}
		_examinee = _examinee->getNextExaminee();
	}
	if (!deleted) {
		cout << "δ�ҵ��ÿ�����������������Ҫɾ���Ŀ����Ŀ��ţ�";
		int num;
		cin >> num;
		deleteExaminee(num);
	}
}
Examinee* ExamineeList::searchExaminee(int num) {
	Examinee* _examinee = head_examinee;
	bool finded = false;
	for (int i = 0; i < ExamineeAmount; i++){
		if (_examinee->getExam_num() == num){
			cout << "�ÿ�����ϢΪ��\n����\t����\t�Ա�\t����\t��������\n" << *_examinee << endl;
			finded = true;
			break;
		}
		_examinee = _examinee->getNextExaminee();
	}
	if (!finded){
		cout << "δ�ҵ��ÿ�����" << endl;
		return NULL;
	}
	return _examinee;
}
void ExamineeList::modificationExaminee(int num) {
	while (true) {
		if (!binary_search(num_vec.begin(), num_vec.end(), num))	{
			cout << "����������Ҫ�޸ĵĿ����Ŀ��ţ�";
			cin >> num;
		}
		else{
			break;
		}
	}
	Examinee* _examinee = searchExaminee(num);
	vector<int>::iterator in = num_vec.begin();
	for (; in < num_vec.end(); in++) {
		if (*in == num) {
			num_vec.erase(in);
			break;
		}
	}
	cout << "����������ÿ�������Ϣ�����ţ��������Ա����估������𣩣�" << endl;
	int _num, _age;
	string _name, _type, _sex;
	bool bool_sex = false;
	cin >> _num >> _name >> _sex >> _age >> _type;
	while (ifNumExist(_num)) {
		cout << "����" << _num << "�Ѵ��ڣ�����������ÿ����Ŀ��ţ��������Ա����估�������" << endl;
		cin >> _num >> _name >> _sex >> _age >> _type;
	};
	num_vec.push_back(_num);
	if (_sex == "��") { bool_sex = true; }
	_examinee->setExam_num(_num);
	_examinee->setName(_name);
	_examinee->setSex(bool_sex);
	_examinee->setAge(_age);
	_examinee->setType(_type);
	cout << "�ÿ�����Ϣ���޸ģ�" << endl;
}
void ExamineeList::countExaminee(int info) {
	switch (info)
	{
	case 1: {
		string name;
		cout << "��������Ҫͳ�Ƶ�������";
		cin >> name;
		Examinee* _examinee = head_examinee;
		int count = 0;
		cout << "ͳ�Ƶ����Ϊ��\n����\t����\t�Ա�\t����\t��������\n";
		for (int i = 0; i < ExamineeAmount; i++){
			if (_examinee->getName() == name) {
				count++;
				cout << *_examinee << endl;
			}
			_examinee = _examinee->getNextExaminee();
		}
		cout << "����" << count << "������Ϊ" << name << "�Ŀ�����\n";
		break;
	};
	case 2: {
		string sex;
		cout << "��������Ҫͳ�Ƶ��Ա�";
		cin >> sex;
		while (sex != "��" && sex != "Ů") {
			cout << "��������Ա��������������룺";
			cin >> sex;
		}
		Examinee* _examinee = head_examinee;
		int count = 0;
		cout << "ͳ�Ƶ����Ϊ��\n����\t����\t�Ա�\t����\t��������\n";
		for (int i = 0; i < ExamineeAmount; i++) {
			if (_examinee->getSex() == sex) {
				count++;
				cout << *_examinee << endl;
			}
			_examinee = _examinee->getNextExaminee();
		}
		cout << "����" << count << "���Ա�Ϊ" << sex << "�Ŀ�����\n";
		break;
	};
	case 3: {
		int age;
		cout << "��������Ҫͳ�Ƶ����䣺";
		cin >> age;
		Examinee* _examinee = head_examinee;
		int count = 0;
		cout << "ͳ�Ƶ����Ϊ��\n����\t����\t�Ա�\t����\t��������\n";
		for (int i = 0; i < ExamineeAmount; i++) {
			if (_examinee->getAge() == age) {
				count++;
				cout << *_examinee << endl;
			}
			_examinee = _examinee->getNextExaminee();
		}
		cout << "����" << count << "������Ϊ" << age << "�Ŀ�����\n";
		break;
	};
	case 4: {
		string type;
		cout << "��������Ҫͳ�Ƶı������ͣ�";
		cin >> type;
		Examinee* _examinee = head_examinee;
		int count = 0;
		cout << "ͳ�Ƶ����Ϊ��\n����\t����\t�Ա�\t����\t��������\n";
		for (int i = 0; i < ExamineeAmount; i++) {
			if (_examinee->getType() == type) {
				count++;
				cout << *_examinee << endl;
			}
			_examinee = _examinee->getNextExaminee();
		}
		cout << "����" << count << "����������Ϊ" << type << "�Ŀ�����\n";
		break;
	}
	default:
		break;
	}
}