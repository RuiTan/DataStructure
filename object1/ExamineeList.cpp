#include "ExamineeList.h"

ExamineeList::ExamineeList(istream &in){
	head_examinee = examinee =  NULL;

	cout << "首先请建立考生信息系统！\n请输入考生人数：";
	cin >> ExamineeAmount;
	do {
		if (ExamineeAmount > MAXAMOUNT || ExamineeAmount <= 0) {
			cout << "输入的考生人数不符合要求，请重新输入：";
			cin >> ExamineeAmount;
		}
		else break;
	} while(true);

	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别：" << endl;
	for (int i = 0; i < ExamineeAmount; i++) {
		//由于获取考生信息是通过一行一行输入，因此解析考生信息将转化为解析字符串，而由于输入的不确定性很大，因此这里就不采用解析字符串的方法，而是直接从输入端获取各个值
		int _num, _age;
		string _name, _type, _sex;
		bool bool_sex = false;
		in >> _num >> _name >> _sex >> _age >> _type;
		while (ifNumExist(_num)) {
			cout << "考号" << _num << "已存在，请重新输入该考生的考号，姓名，性别，年龄及报考类别：" << endl;
			cin >> _num >> _name >> _sex >> _age >> _type;
		} ;//考生已存在，不能重复添加考生，判断依据是考号（姓名及其他信息均可存在相同情况，但是考号是一人一个）

		num_vec.push_back(_num);

		if (_sex == "男") { bool_sex = true; }
		//性别同样也是很难通过输入确定，这里只假设输入“男”时，为男性，其余情况均为女性

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
	for (int i = 0; i < ExamineeAmount; i++){
		deleteExaminee(num_vec[0]);
	}
}

bool ExamineeList::ifNumExist(int num) {
	return binary_search(num_vec.begin(), num_vec.end(), num);
	//二分法查找指定考号考生是否存在（对于vector来说，二分法并不是一个效率高的算法，因其并非是有序的，因此二分法应用在vector上时需要先按一定顺序将其排序而后通过二分法搜索。这是个效率低下的操作）
}

void ExamineeList::printList() {
	//打印当前的考生信息
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
	//插入考生，指定考生位置，这里规定当考生位置大于当前考生数量时，便将考生位置置于列表最后
	cout << "请选择你要插入的考生位置(当前共有考生" << ExamineeAmount << "名)：";
	int index;
	cin >> index;
	while (index <= 0) {
		cout << "您输入的考生位置有误，请重新输入：";
		cin >> index;
	};

	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄及报考类别：" << endl;
	int _num, _age;
	string _name, _type, _sex;
	bool bool_sex = false;
	cin >> _num >> _name >> _sex >> _age >> _type;
	if (ifNumExist(_num)){
		cout << "考号为" << _num << "的考生已存在，请重新输入要插入的考生的考号，姓名，性别，年龄及报考类别：" << endl;
		cin >> _num >> _name >> _sex >> _age >> _type;
	}

	num_vec.push_back(_num);
	if (_sex == "男") { bool_sex = true; }
	Examinee *p_exa = new Examinee(_num, _name, bool_sex, _age, _type);
	if (index > ExamineeAmount) {
		//输入位置大于总人数时
		p_exa->setPrevExaminee(*tail_examinee);
		tail_examinee->setNextExaminee(*p_exa);
		tail_examinee = p_exa;
	}
	else  if (index == 1) {
		//输入位置为列表头时
		p_exa->setNextExaminee(*head_examinee);
		head_examinee->setPrevExaminee(*p_exa);
		head_examinee = p_exa;
	}
	else {
		//输入位置为列表内部
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
	//通过指定的考生考号删除考生信息
	Examinee* _examinee = head_examinee;
	bool deleted = false;
	for (int i = 0; i < ExamineeAmount; i++){
		if (_examinee->getExam_num() == num){
			deleted = true;
			if (_examinee == head_examinee){
				//删除头结点
				head_examinee = head_examinee->getNextExaminee();
				head_examinee->noPrevExaminee();
				_examinee->noNextExaminee();
			}
			else if (_examinee == tail_examinee) {
				//删除尾结点
				tail_examinee = tail_examinee->getPrevExaminee();
				tail_examinee->noNextExaminee();
				_examinee->noPrevExaminee();
			}
			else {
				//删除中间结点
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
					//跳出遍历num_vec循环
				}
			}//删除vector中的考生号码，使得考生列表与考号容器保持一致
			break;
			//找到该考生了并已删除，跳出循环
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
	//遍历考生列表，查找指定考号的考生，并返回该考生的指针
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
	//修改考生信息，考生列表采取直接修改考生数据的方式，而考号容器采用先删除后添加的方式
	Examinee* _examinee = searchExaminee(num);
	while (_examinee == nullptr){
		cout << "该考生不存在，请重新输入要修改的考生的考号：";
		cin >> num;
		Examinee* _examinee = searchExaminee(num);
	}
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
	//通过指定信息统计考生列表中的情况
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