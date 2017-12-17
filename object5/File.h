//
// Created by Kevin on 2017/10/22.
//

#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iomanip>//setw�������������룩ͷ�ļ�
#include <sstream>//�ַ���������ͷ�ļ�
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


File::File() {}
File::File(string _file_name) {
	file_name = _file_name;
	out_file.open(file_name, ios::app);
	in_file.open(file_name);
}
File::~File() {}
Word* File::wordExist(string _word) {
	vector<Word>::iterator i_vec = word_vec.begin();
	for (; i_vec != word_vec.end(); i_vec++) {
		if (_word == i_vec->word) return &(*i_vec);
	}
	return NULL;
}
void File::addToWordVec(string _word) {
	if (!wordExist(_word)) {
		Word temp(_word, 1);
		word_vec.push_back(temp);
	}
	else {
		wordExist(_word)->count += 1;
	}
}
void File::countWords() {
	vector<Word>(word_vec).swap(word_vec);//���֮ǰ�����word
	string temp;
	while (in_file >> temp) {
		addToWordVec(temp);
	}
	cout << "�������������������������ʡ�������������������������������\n";
	vector<Word>::iterator i_vec = word_vec.begin();
	int word_amount = 0;
	for (; i_vec != word_vec.end(); i_vec++) {
		word_amount += i_vec->count;
		cout << "\t" << right << setw(16) << i_vec->word << "\t\t\t" << right << i_vec->count << endl;
	}
	cout << "������������������������������" << file_name << "�ĵ�������Ϊ" << word_amount << "����" << endl;
}
void File::countWordsInFile() {
	in_file.clear();
	in_file.seekg(0);//������������棬������ָ�뷵�ص��ļ�ͷ
	cout << "������Ҫ�����ĵ��ʣ�";
	string input_word, temp;
	cin >> input_word;
	int amount = 0;
	while (in_file >> temp){
		if (temp == input_word)	{
			amount++;
		}
	}
	cout << "����" << input_word << "���ı��ļ�" << file_name << "�й�������" << amount << "��" << endl;
}
void File::locateWordsInFile() {
	in_file.clear();
	in_file.seekg(0);//������������棬������ָ�뷵�ص��ļ�ͷ
	cout << "������Ҫ�����ĵ��ʣ�";
	string input_word, out_line;
	cin >> input_word;
	vector<int> line_nums, word_index, amounts;
	int line_num = 0, amount = 0, index_size = 0;
	while (getline(in_file, out_line)) {
		line_num++;
		amount = 0;
		locateWordsInLine(out_line, input_word, word_index, amount, amounts);
		if (word_index.size() != index_size) {
			line_nums.push_back(line_num);
		}
		index_size = word_index.size();
	}
	if (line_nums.size() == 0) {
		cout << "�ļ�" << file_name << "����û�е���" << input_word << endl;
	}
	else {
		vector<int>::iterator i_line_nums = line_nums.begin(),
			i_word_index = word_index.begin(),
			i_amounts = amounts.begin();
		for (; i_line_nums != line_nums.end(); i_line_nums++, i_amounts++) {
			cout << "�кţ�" << *i_line_nums << ",������" << *i_amounts << "��ʼλ�÷ֱ�Ϊ��";
			for (int i = 0; i < *i_amounts; i++) {
				cout << "��" << *i_word_index+1 << "���ַ� ";
				i_word_index++;
			}
			cout << endl;
		}
	}
}
void File::locateWordsInLine(string out_line, string input_word, vector<int>& word_index, int &amount, vector<int>& amounts) {
	istringstream out_line_stream(out_line);//�����ַ���������
	string temp;
	int index = 0;
	while (out_line_stream >> temp) {
		if (temp == input_word) {
			word_index.push_back(index);
			amount++;
		}
		index += temp.size() + 1;
	}
	if (amount != 0) {
		amounts.push_back(amount);
	}
}

#endif //INC_5_���ʼ���ͳ��ϵͳ_FILE_H
