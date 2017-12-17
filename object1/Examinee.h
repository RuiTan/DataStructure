#pragma once
#ifndef EXAMINEE_H
#define EXAMINEE_H

#include <iostream>
#include <string>
using namespace std;

/*
	Examinee�������洢����������Ϣ����Ҫ���ݾ��ǿ����Ļ�����Ϣ�Լ�һ��ָ��ǰһ����һ��ָ���һ������ָ��
*/

class Examinee {
public:
	Examinee();
	Examinee(int _num, string _name, bool _sex, int _age, string _type);

	~Examinee();

	void setExam_num(int);
	void setName(string);
	void setSex(bool);
	void setAge(int);
	void setType(string);
	//���ÿ���������Ϣ

	int getExam_num();
	string getName();
	string getSex();
	int getAge();
	string getType();
	//��ȡ����������Ϣ	

	Examinee* getNextExaminee();
	Examinee* getPrevExaminee();
	//��ȡǰһ�������ͺ�һ������

	void setNextExaminee(Examinee&);
	//������������Ϊ��ǰ�����ĺ�һ������
	void setPrevExaminee(Examinee&);
	//������������Ϊ��ǰ������ǰһ������

	void noPrevExaminee();
	//����ǰ����ǰ����ָ���ÿ�
	void noNextExaminee();
	//����ǰ��������ָ���ÿ�

	friend ostream& operator<<(ostream&, Examinee&);

private:
	int exam_num;
	string name;
	bool sex;
	int age;
	string type;
	//����������Ϣ�����š��������Ա����䡢�������

	Examinee* next_examinee;
	Examinee* prev_examinee;
	//��������ǰ������ָ��
};


Examinee::Examinee(){
	exam_num = 0;
	name = "";
	sex = true;
	age = 0;
	type = "";
	next_examinee = NULL;
	prev_examinee = NULL;
}
Examinee::Examinee(int _num, string _name, bool _sex, int _age, string _type) :exam_num(_num), name(_name), sex(_sex), age(_age), type(_type) {}
Examinee::~Examinee(){
	exam_num = 0;
	name = "";
	sex = true;
	age = 0;
	type = "";
}

void Examinee::setExam_num(int _num) { exam_num = _num; }
void Examinee::setName(string _name) { name = _name; }
void Examinee::setSex(bool _sex) { sex = _sex; }
void Examinee::setAge(int _age) { age = _age; }
void Examinee::setType(string _type) { type = _type; }
void Examinee::setNextExaminee(Examinee& _examinee) {
	next_examinee = &_examinee;
}
void Examinee::setPrevExaminee(Examinee& _examinee) {
	prev_examinee = &_examinee;
}
void Examinee::noNextExaminee() {
	next_examinee = NULL;
}
void Examinee::noPrevExaminee() {
	prev_examinee = NULL;
}

int Examinee::getExam_num() { return exam_num; }
string Examinee::getName() { return name;}
string Examinee::getSex() { return sex ? "��" : "Ů"; }
int Examinee::getAge() { return age; }
string Examinee::getType() { return type; }
Examinee* Examinee::getNextExaminee() { return next_examinee; }
Examinee* Examinee::getPrevExaminee() { return prev_examinee; }

ostream & operator<<(ostream &os,  Examinee &examinee){
	os << examinee.getExam_num() << "\t" << examinee.getName() << "\t" << examinee.getSex() << "\t" << examinee.getAge() << "\t" << examinee.getType();
	return os;
}


#endif // !EXAMINEE_H
