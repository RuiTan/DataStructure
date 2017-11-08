#pragma once
#ifndef EXAMINEELIST_H
#define EXAMINEE_LIST_H
#define MAXAMOUNT 5000

#include "Examinee.h"
#include <vector>
#include <iterator>
#include <algorithm>

/*
	ExamineeList���������������ݵĿ⣬��ʹ��˫��������ʵ�֣�ͨ���ڲ�������ɶԿ�����Ϣ�Ľ��������ң����룬�޸ģ�ɾ���ȹ���
*/

static int ExamineeAmount = 0;

class ExamineeList {
public:
	ExamineeList(istream &in = cin);
	~ExamineeList();
	bool ifNumExist(int);
	void printList();
	void operateList(int);
	void insertExaminee();
	void deleteExaminee(int);
	Examinee* searchExaminee(int);
	void modificationExaminee(int);
	void countExaminee(int);
private:
	Examinee* examinee;
	Examinee* head_examinee;
	Examinee* tail_examinee;
	vector<int> num_vec;
};

#endif // 