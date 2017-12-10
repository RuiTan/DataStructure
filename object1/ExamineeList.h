#pragma once
#ifndef EXAMINEELIST_H
#define EXAMINEE_LIST_H
#define MAXAMOUNT 10000

#include "Examinee.h"
#include <vector>
#include <iterator>
#include <algorithm>

/*
	ExamineeList类是用来考生数据的库，它使用双向链表来实现，其属于不带头尾结点的，通过内部函数完成对考生信息的建立，查找，插入，修改，删除等功能
*/

static int ExamineeAmount = 0;

class ExamineeList {
public:
	ExamineeList(istream &in = cin);
	//链表的构造函数，可通过更改参数选择通过命令行输入或者通过文件输入
	~ExamineeList();

	bool ifNumExist(int);
	//查找考号
	void printList();
	//打印考生列表
	void operateList(int);
	//选择要对考生列表进行的操作
	void insertExaminee();
	//添加考生
	void deleteExaminee(int);
	//删除考生
	Examinee* searchExaminee(int);
	//通过考号查找考生，返回该考生的指针
	void modificationExaminee(int);
	//修改指定考号的考生信息
	void countExaminee(int);
	//计算考生人数

private:
	Examinee* examinee;
	//总是指向当前考生
	Examinee* head_examinee;
	Examinee* tail_examinee;
	//头尾指针
	vector<int> num_vec;
	//存放考生考号的容器
};

#endif 