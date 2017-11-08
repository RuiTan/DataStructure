#include "Family.h"
#include <sstream>

Family::Family() {
	cout << "**\t\t\t���׹���ϵͳ\t\t\t**\n"
		<< "==========================================================\n"
		<< "**\t\t\tA -- ���Ƽ���\t\t\t**\n"
		<< "**\t\t\tB -- ��Ӽ�ͥ��Ա\t\t**\n"
		<< "**\t\t\tC -- ��ɢ�ֲ���ͥ\t\t**\n"
		<< "**\t\t\tD -- ���ļ�ͥ��Ա����\t\t**\n"
		<< "**\t\t\tE -- �˳�����\t\t\t**\n"
		<< "==========================================================\n";
	cout << "���Ƚ���һ�����ף�\n���������ȵ�������";
	string _name;
	cin >> _name;
	head = new Member(_name);
	addMemberToMap(_name, head);
	cout << "�˼���������ǣ�" << _name << endl << endl;
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
	cout << "��ѡ��Ҫִ�еĲ�����";
	cin >> operate;
	switch (operate)
	{
	case 'A': {
		cout << "������Ҫ������ͥ���˵�������";
		cin >> _name;
		while (!searchInFamily(_name)) {
			cout << "������û�и��ˣ����������룺";
			cin >> _name;
		}
		while (Names.find(_name)->second->offspring != NULL) {
			cout << "�����Ѿ��м�ͥ�ˣ����������룺";
			cin >> _name;
		}
		int _offsprings;
		cout << "������" << _name << "�Ķ�Ů������";
		cin >> _offsprings;
		while (_offsprings < 1) {
			cout << "���������������������룺";
			cin >> _offsprings;
		}
		cout << "����������" << _name << "����Ů��������";
		completeFamily(_name, _offsprings);
		cout << endl;
		cout << head->name;
		printFamily(head);
		setOperator();
		break;
	}
	case 'B': {
		cout << "������Ҫ�����Ů���˵�������";
		cin >> _name;
		while (!searchInFamily(_name)) {
			cout << "������û�и��ˣ����������룺";
			cin >> _name;
		}
		string _offspring;
		cout << "������" << _offspring << "����ӵ���Ů��������";
		cin >> _offspring;
		while (searchInFamily(_offspring) != NULL) {
			cout << "��Ϊ" << _offspring << "�����Ѵ��ڼ�������������룺";
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
		cout << "������Ҫ��ɢ�ļ�ͥ���˵�������";
		cin >> _name;
		while (!searchInFamily(_name)) {
			cout << "������û�и��ˣ����������룺";
			cin >> _name;
		}
		cout << "Ҫ��ɢ�����ǣ�" << _name << endl;
		Member *temp = Names.find(_name)->second;
		if (temp->offspring == NULL) {
			cout << "����û����Ů���޷���ɢ\n";
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
		cout << "������Ҫ�����������˵�Ŀǰ������";
		cin >> _name;
		while (!searchInFamily(_name)) {
			cout << "������û�и��ˣ����������룺";
			cin >> _name;
		}
		string _offspring;
		cout << "��������ĺ��������";
		cin >> _offspring;
		while (searchInFamily(_offspring) != NULL) {
			cout << "��Ϊ" << _offspring << "�����Ѵ��ڼ�������������룺";
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
		cout << "����Ĳ�������ӦΪA~E" << endl;
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
			cout << "�������Ѵ��������е�����" << _offspring;
			cout << ",������������Ů��������";
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
