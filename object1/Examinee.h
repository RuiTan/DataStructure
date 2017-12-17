#pragma once
#ifndef EXAMINEE_H
#define EXAMINEE_H

#include <iostream>
#include <string>
using namespace std;

/*
	Examinee类用来存储单个考生信息，主要数据就是考生的基本信息以及一个指向前一考生一个指向后一考生的指针
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
	//设置考生基本信息

	int getExam_num();
	string getName();
	string getSex();
	int getAge();
	string getType();
	//获取考生基本信息	

	Examinee* getNextExaminee();
	Examinee* getPrevExaminee();
	//获取前一个考生和后一个考生

	void setNextExaminee(Examinee&);
	//将参数考生设为当前考生的后一个考生
	void setPrevExaminee(Examinee&);
	//将参数考生设为当前考生的前一个考生

	void noPrevExaminee();
	//将当前考生前考生指针置空
	void noNextExaminee();
	//将当前考生后考生指针置空

	friend ostream& operator<<(ostream&, Examinee&);

private:
	int exam_num;
	string name;
	bool sex;
	int age;
	string type;
	//考生基本信息：考号、姓名、性别、年龄、报考类别

	Examinee* next_examinee;
	Examinee* prev_examinee;
	//考生链表前后考生的指针
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
string Examinee::getSex() { return sex ? "男" : "女"; }
int Examinee::getAge() { return age; }
string Examinee::getType() { return type; }
Examinee* Examinee::getNextExaminee() { return next_examinee; }
Examinee* Examinee::getPrevExaminee() { return prev_examinee; }

ostream & operator<<(ostream &os,  Examinee &examinee){
	os << examinee.getExam_num() << "\t" << examinee.getName() << "\t" << examinee.getSex() << "\t" << examinee.getAge() << "\t" << examinee.getType();
	return os;
}


#endif // !EXAMINEE_H
