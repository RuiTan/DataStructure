#pragma once
#include <iostream>
#include <string>
using namespace std;


class Member {
	friend class Family;
public:
	Member() {
		parent = offspring = pre_bro = next_bro = NULL;
		offsprings = 0;
	};
	~Member() {};
	Member(Member &member) {
		name = member.name;
		parent = member.parent;
		offspring = member.offspring;
		pre_bro = member.pre_bro;
		next_bro = member.next_bro;
		offsprings = 0;
	};
	Member(string _name) {
		Member();
		name = _name;
	};
private:
	string name;
	int offsprings;
	Member *parent, *offspring, *pre_bro, *next_bro;
};