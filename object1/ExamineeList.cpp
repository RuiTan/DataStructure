#include "ExamineeList.h"

ExamineeList::ExamineeList(istream &in){
	head_examinee = examinee =  NULL;

	cout << "首先请建立考生信息系统！\n请输入考生人数：";
	cin >> ExamineeAmount;
	do {
		if (ExamineeAmount > MAXAMOUNT || ExamineeAmount < 0) {
			cout << "输入的考生人数不符合要求，请重新输入：";
			cin >> ExamineeAmount;
		}
		else break;
	} while(true);

	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别：" << endl;
	for (int i = 0; i < ExamineeAmount; i++) {
		int _num, _age;
		string _name, _type, _sex;
		bool bool_sex = false;
		in >> _num >> _name >> _sex >> _age >> _type;
		while (ifNumExist(_num)) {
			cout << "考号" << _num << "已存在，请重新输入该考生的考号，姓名，性别，年龄及报考类别：" << endl;
			cin >> _num >> _name >> _sex >> _age >> _type;
		} ;
		num_vec.push_back(_num);
		if (_sex == "男") { bool_sex = true; }
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
	cout << "\n*************考生报名系统情况*************";
	if (ExamineeAmount == 0){
		cout << "*****考生报名系统中暂时没有考生信息！*****\n";
	}
	else {
		cout << "\n考号\t姓名\t性别\t年龄\t报考类型\n";
		cout << *head_examinee << endl;
		Examinee* _examinee = head_examinee;
		for (int i = 1; i < ExamineeAmount; i++) {
			cout << *_examinee->getNextExaminee() << endl;
			_examinee = _examinee->getNextExaminee();
		}
	}
	cout << "******************************************" << endl;
	cout << "\n请选择您要进行的操作：（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
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
		cout << "请输入要删除的考生的考号：";
		int num;
		cin >> num;
		deleteExaminee(num);
		break;
	};
	case 3: {
		cout << "请输入要查找的考生的考号：";
		int num;
		cin >> num;
		searchExaminee(num);
		break;
	};
	case 4: {
		cout << "请输入要修改的考生的考号：";
		int num;
		cin >> num;
		modificationExaminee(num);
		break;
	};
	case 5: {
		cout << "请输入要统计的信息（1为姓名，2为性别，3为年龄，4为报考类型）：";
		int info;
		cin >> info;
		countExaminee(info);
		break;
	}
	default: {
		cout << "您的输入有误，请重新选择您要进行的操作：（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
		int op;
		cin >> op;
		operateList(op);
	};
	};
	printList();
	cout << "\n请选择您要进行的操作：（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	cin >> op;
	operateList(op);
}
void ExamineeList::insertExaminee() {
	cout << "请选择你要插入的考生位置(当前共有考生" << ExamineeAmount << "名)：";
	int index;
	cin >> index;
	while (index < 0) {
		cout << "您输入的考生位置有误，请重新输入：";
		cin >> index;
	};
	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别：" << endl;
	int _num, _age;
	string _name, _type, _sex;
	bool bool_sex = false;
	cin >> _num >> _name >> _sex >> _age >> _type;
	if (binary_search(num_vec.begin(), num_vec.end(), _num)){
		cout << "考号为" << _num << "的考生已存在，请重新输入要插入的考生的考号，姓名，性别，年龄及报考类别：" << endl;
		cin >> _num >> _name >> _sex >> _age >> _type;
	}
	num_vec.push_back(_num);
	if (_sex == "男") { bool_sex = true; }
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
			cout << "您将要删除的考生信息为：" << *_examinee << endl;
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
		cout << "未找到该考生，请重新输入您要删除的考生的考号：";
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
			cout << "该考生信息为：\n考号\t姓名\t性别\t年龄\t报考类型\n" << *_examinee << endl;
			finded = true;
			break;
		}
		_examinee = _examinee->getNextExaminee();
	}
	if (!finded){
		cout << "未找到该考生！" << endl;
		return NULL;
	}
	return _examinee;
}
void ExamineeList::modificationExaminee(int num) {
	while (true) {
		if (!binary_search(num_vec.begin(), num_vec.end(), num))	{
			cout << "请重新输入要修改的考生的考号：";
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
	cout << "请重新输入该考生的信息（考号，姓名，性别，年龄及报考类别）：" << endl;
	int _num, _age;
	string _name, _type, _sex;
	bool bool_sex = false;
	cin >> _num >> _name >> _sex >> _age >> _type;
	while (ifNumExist(_num)) {
		cout << "考号" << _num << "已存在，请重新输入该考生的考号，姓名，性别，年龄及报考类别：" << endl;
		cin >> _num >> _name >> _sex >> _age >> _type;
	};
	num_vec.push_back(_num);
	if (_sex == "男") { bool_sex = true; }
	_examinee->setExam_num(_num);
	_examinee->setName(_name);
	_examinee->setSex(bool_sex);
	_examinee->setAge(_age);
	_examinee->setType(_type);
	cout << "该考生信息已修改！" << endl;
}
void ExamineeList::countExaminee(int info) {
	switch (info)
	{
	case 1: {
		string name;
		cout << "请输入您要统计的姓名：";
		cin >> name;
		Examinee* _examinee = head_examinee;
		int count = 0;
		cout << "统计的情况为：\n考号\t姓名\t性别\t年龄\t报考类型\n";
		for (int i = 0; i < ExamineeAmount; i++){
			if (_examinee->getName() == name) {
				count++;
				cout << *_examinee << endl;
			}
			_examinee = _examinee->getNextExaminee();
		}
		cout << "共有" << count << "个姓名为" << name << "的考生。\n";
		break;
	};
	case 2: {
		string sex;
		cout << "请输入您要统计的性别：";
		cin >> sex;
		while (sex != "男" && sex != "女") {
			cout << "您输入的性别有误，请重新输入：";
			cin >> sex;
		}
		Examinee* _examinee = head_examinee;
		int count = 0;
		cout << "统计的情况为：\n考号\t姓名\t性别\t年龄\t报考类型\n";
		for (int i = 0; i < ExamineeAmount; i++) {
			if (_examinee->getSex() == sex) {
				count++;
				cout << *_examinee << endl;
			}
			_examinee = _examinee->getNextExaminee();
		}
		cout << "共有" << count << "个性别为" << sex << "的考生。\n";
		break;
	};
	case 3: {
		int age;
		cout << "请输入您要统计的年龄：";
		cin >> age;
		Examinee* _examinee = head_examinee;
		int count = 0;
		cout << "统计的情况为：\n考号\t姓名\t性别\t年龄\t报考类型\n";
		for (int i = 0; i < ExamineeAmount; i++) {
			if (_examinee->getAge() == age) {
				count++;
				cout << *_examinee << endl;
			}
			_examinee = _examinee->getNextExaminee();
		}
		cout << "共有" << count << "个年龄为" << age << "的考生。\n";
		break;
	};
	case 4: {
		string type;
		cout << "请输入您要统计的报考类型：";
		cin >> type;
		Examinee* _examinee = head_examinee;
		int count = 0;
		cout << "统计的情况为：\n考号\t姓名\t性别\t年龄\t报考类型\n";
		for (int i = 0; i < ExamineeAmount; i++) {
			if (_examinee->getType() == type) {
				count++;
				cout << *_examinee << endl;
			}
			_examinee = _examinee->getNextExaminee();
		}
		cout << "共有" << count << "个报考类型为" << type << "的考生。\n";
		break;
	}
	default:
		break;
	}
}