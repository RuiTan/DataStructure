#pragma once
#include "Member.h"
#include <map>

/*
	Family类采用类似广义表的存储方式来存储家族系统，正常情况下，在一个家族中，每个成员都只有一个父（母）亲（这里是因为不考虑嫁入或嫁出的成员），而可以有多个子女，因此广义表是个不错的选择
*/

class Family {
	friend class Member;
public:
	Family();
	~Family();
protected:
	void setOperator();
	//选择要进行的操作
	void completeFamily(const string _parent, const int _offstpings);
	//完善指定成员的家庭，当该成员已经有家庭时，不得完善（此时若需要完善可使用insertToFamily函数而非此函数）
	void insertToFamily(const string _parent, const string _offstping);
	//向指定成员添加子女
	void dissolveFamily(Member *_name);
	//解散指定家庭
	void changeMemberName(const string _name, const string _change);
	//更改指定成员的姓名	
	void addMemberToMap(const string _name, Member *member);
	//将成员添加到“姓名->成员”的映射容器中
	bool searchInFamily(const string _name);
	//查找某一成员，由于存在“姓名->成员”的映射，因此这里采用对map容器进行二分查找，是个效率比较高的方法
	void printFamily(Member *_member);
	//输出当前家谱情况

	map<string, Member*> Names;
	//“姓名->成员”的映射，用于快速定位成员
	Member *head;
	//家族中的祖先
};