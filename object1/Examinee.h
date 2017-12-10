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
	Examinee(int, string, bool, int, string);
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

#endif // !EXAMINEE_H
