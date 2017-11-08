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
