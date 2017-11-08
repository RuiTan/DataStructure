//
// Created by Kevin on 2017/10/22.
//

#ifndef INC_5_单词检索统计系统_FILE_H
#define INC_5_单词检索统计系统_FILE_H
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include "System.h"
#include "Word.h"
using namespace std;

class Word;
class File{
    friend class System;

public:
    File();
	File(string _file_name);
    ~File();
	Word* wordExist(string _word);
	void addToWordVec(string _word);
	void countWords();
	void locateWordsInFile();
	void countWordsInFile();
	void locateWordsInLine(string, string, vector<int>&, int&, vector<int>&);
private:
    string file_name;
    ofstream out_file;
	ifstream in_file;
	File* next_file;
	vector<Word> word_vec;
};

#endif //INC_5_单词检索统计系统_FILE_H
