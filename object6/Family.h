#pragma once
#include "Member.h"
#include <map>


class Family {
	friend class Member;
public:
	Family();
	~Family();
protected:
	void setOperator();
	void completeFamily(const string _parent, const int _offstpings);
	void insertToFamily(const string _parent, const string _offstping);
	void dissolveFamily(Member *_name);
	void changeMemberName(const string _name, const string _change);
	void addMemberToMap(const string _name, Member *member);
	bool searchInFamily(const string _name);
	void printFamily(Member *_member);
	map<string, Member*> Names;
	Member *head;
};