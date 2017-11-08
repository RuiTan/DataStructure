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
	void setNextExaminee(Examinee&);
	void setPrevExaminee(Examinee&);
	void noPrevExaminee();
	void noNextExaminee();

	int getExam_num();
	string getName();
	string getSex();
	int getAge();
	string getType();
	Examinee* getNextExaminee();
	Examinee* getPrevExaminee();

	friend ostream& operator<<(ostream&, Examinee&);

private:
	int exam_num;
	string name;
	bool sex;
	int age;
	string type;
	Examinee* next_examinee;
	Examinee* prev_examinee;
};

#endif // !EXAMINEE_H
