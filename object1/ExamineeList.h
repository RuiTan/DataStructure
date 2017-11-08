#pragma once
#ifndef EXAMINEELIST_H
#define EXAMINEE_LIST_H
#define MAXAMOUNT 5000

#include "Examinee.h"
#include <vector>
#include <iterator>
#include <algorithm>

/*
	ExamineeList类是用来考生数据的库，它使用双向链表来实现，通过内部函数完成对考生信息的建立，查找，插入，修改，删除等功能
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