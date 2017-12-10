#include "Family.h"
#include <sstream>

Family::Family() {
	cout << "**\t\t\t家谱管理系统\t\t\t**\n"
		<< "==========================================================\n"
		<< "**\t\t\tA -- 完善家谱\t\t\t**\n"
		<< "**\t\t\tB -- 添加家庭成员\t\t**\n"
		<< "**\t\t\tC -- 解散局部家庭\t\t**\n"
		<< "**\t\t\tD -- 更改家庭成员姓名\t\t**\n"
		<< "**\t\t\tE -- 退出程序\t\t\t**\n"
		<< "==========================================================\n";
	cout << "首先建立一个家谱！\n请输入祖先的姓名：";
	string _name;
	cin >> _name;
	head = new Member(_name);
	addMemberToMap(_name, head);
	cout << "此家族的祖先是：" << _name << endl << endl;
	setOperator();
}
Family::~Family() {
	dissolveFamily(head);
	Names.erase(head->name);
	delete head;
}
void Family::setOperator() {
	char operate;
	string _name;
	cout << "请选择要执行的操作：";
	cin >> operate;
	switch (operate)
	{
	case 'A': {
		cout << "请输入要建立家庭的人的姓名：";
		cin >> _name;
		while (!searchInFamily(_name)) {
			cout << "家谱中没有该人，请重新输入：";
			cin >> _name;
		}
		while (Names.find(_name)->second->offspring != NULL) {
			cout << "该人已经有家庭了，请重新输入：";
			cin >> _name;
		}
		int _offsprings;
		cout << "请输入" << _name << "的儿女人数：";
		cin >> _offsprings;
		while (_offsprings < 1) {
			cout << "人数输入有误，请重新输入：";
			cin >> _offsprings;
		}
		cout << "请依次输入" << _name << "的子女的姓名：";
		completeFamily(_name, _offsprings);
		cout << endl;
		cout << head->name;
		printFamily(head);
		setOperator();
		break;
	}
	case 'B': {
		cout << "请输入要添加子女的人的姓名：";
		cin >> _name;
		while (!searchInFamily(_name)) {
			cout << "家谱中没有该人，请重新输入：";
			cin >> _name;
		}
		string _offspring;
		cout << "请输入" << _offspring << "新添加的子女的姓名：";
		cin >> _offspring;
		while (searchInFamily(_offspring) != NULL) {
			cout << "名为" << _offspring << "的人已存在家谱里，请重新输入：";
			cin >> _offspring;
		}
		insertToFamily(_name, _offspring);
		cout << endl;
		cout << head->name;
		printFamily(head);
		setOperator();
		break;
	}
	case 'C': {
		cout << "请输入要解散的家庭的人的姓名：";
		cin >> _name;
		while (!searchInFamily(_name)) {
			cout << "家谱中没有该人，请重新输入：";
			cin >> _name;
		}
		cout << "要解散的人是：" << _name << endl;
		Member *temp = Names.find(_name)->second;
		if (temp->offspring == NULL) {
			cout << "该人没有子女，无法解散\n";
		}
		else {
			dissolveFamily(temp->offspring);
			temp->offspring = NULL;
			temp->offsprings = 0;
		}
		cout << endl;
		cout << head->name;
		printFamily(head);
		setOperator();
		break;
	}
	case 'D': {
		cout << "请输入要更改姓名的人的目前姓名：";
		cin >> _name;
		while (!searchInFamily(_name)) {
			cout << "家谱中没有该人，请重新输入：";
			cin >> _name;
		}
		string _offspring;
		cout << "请输入更改后的姓名：";
		cin >> _offspring;
		while (searchInFamily(_offspring) != NULL) {
			cout << "名为" << _offspring << "的人已存在家谱里，请重新输入：";
			cin >> _offspring;
		}
		changeMemberName(_name, _offspring);
		cout << endl;
		cout << head->name;
		printFamily(head);
		setOperator();
		break;
	}
	case 'E':
		exit(1);
	default:
		cout << "输入的操作有误，应为A~E" << endl;
		setOperator();
		break;
	}
}
void Family::addMemberToMap(string _name, Member* member) {
	Names.insert(pair<string, Member*>(_name, member));
}
void Family::completeFamily(string _name, int _offsprings) {
	string _offspring, _offspring2;
	getline(cin, _offspring2);
	getline(cin, _offspring2);
	bool completed = false;
	int count = 0;
	while (true) {
		stringstream name_stream(_offspring2);
		name_stream >> _offspring;
		if (searchInFamily(_offspring)) {
			cout << "家谱中已存在输入中的名字" << _offspring;
			cout << ",请重新输入子女的姓名：";
			getline(cin, _offspring2);
			name_stream.seekg(0);
			name_stream << _offspring2;
			count = 0;
			continue;
		}
		if (count == _offsprings) break;
		count++;
	}
	istringstream name_stream2(_offspring2);
	map<string, Member*>::iterator i_names = Names.find(_name);
	for (int i = 0; i < _offsprings && name_stream2 >> _offspring; i++) {

		insertToFamily(_name, _offspring);
	}
	cout << endl;
}
void Family::insertToFamily(string _parent, string _offspring) {
	Member *member = new Member(_offspring);
	addMemberToMap(_offspring, member);
	Member *temp = Names.find(_parent)->second;
	Names.find(_parent)->second->offsprings++;
	if (Names.find(_parent)->second->offspring == NULL) {
		temp->offspring = member;
		member->parent = temp;
	}
	else {
		temp = temp->offspring;
		while (temp->next_bro != NULL) {
			temp = temp->next_bro;
		}
		temp->next_bro = member;
		member->pre_bro = temp;
		member->parent = Names.find(_parent)->second;
	}
}
void Family::dissolveFamily(Member *_name) {
	if (_name->offspring == NULL && _name->next_bro == NULL) {
		Names.erase(_name->name);
		delete _name;
		return;
	}
	if (_name->offspring != NULL)	
		dissolveFamily(_name->offspring);
	if (_name->next_bro != NULL) 
		dissolveFamily(_name->next_bro);
	Names.erase(_name->name);
	delete _name;
}
void Family::changeMemberName(string _name, string _change) {
	Member *temp = Names.find(_name)->second;
	temp->name = _change;
}
bool Family::searchInFamily(string _name) {
	return Names.find(_name) == Names.end() ? false : true;
}
void Family::printFamily(Member *_member) {
	if (_member->offsprings == 0) {
		return;
	}
	_member = _member->offspring;
	cout << "(";
	cout << _member->name;
	printFamily(_member);
	while (_member->next_bro != NULL) {
		cout << ",";
		cout << _member->next_bro->name;
		_member = _member->next_bro;
		printFamily(_member);
	}
	cout << ")";
}
