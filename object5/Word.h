#pragma once
#ifndef WORD_H
#define WORD_H
#include "System.h"
#include <string>

class Word {
	friend class System;
	friend class File;

public:
	Word();
	Word(std::string _word, int _count);
	~Word();

private:
	std::string word;
	int count;
};
Word::Word(){
	count = 0;
}
Word::Word(std::string _word, int _count):word(_word), count(_count){}
Word::~Word() {};

#endif // !WORD_H
