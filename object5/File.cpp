//
// Created by Kevin on 2017/10/22.
//

#include "File.h"
#include <iomanip>//setw函数（对齐输入）头文件
#include <sstream>//字符串输入流头文件


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
	vector<Word>(word_vec).swap(word_vec);//清空之前留存的word
	string temp;
	while (in_file >> temp) {
		addToWordVec(temp);
	}
	cout << "》》》》》》》》》》》单词《《《《《》》》》》个数《《《《\n";
	vector<Word>::iterator i_vec = word_vec.begin();
	int word_amount = 0;
	for (; i_vec != word_vec.end(); i_vec++) {
		word_amount += i_vec->count;
		cout << "\t" << right << setw(16) << i_vec->word << "\t\t\t" << right << i_vec->count << endl;
	}
	cout << "》》》》》》》》》》》》》》》" << file_name << "的单词总数为" << word_amount << "个！" << endl;
}
void File::countWordsInFile() {
	in_file.clear();
	in_file.seekg(0);//清空输入流缓存，并将读指针返回到文件头
	cout << "请输入要检索的单词：";
	string input_word, temp;
	cin >> input_word;
	int amount = 0;
	while (in_file >> temp){
		if (temp == input_word)	{
			amount++;
		}
	}
	cout << "单词" << input_word << "在文本文件" << file_name << "中共出现了" << amount << "次" << endl;
}
void File::locateWordsInFile() {
	in_file.clear();
	in_file.seekg(0);//清空输入流缓存，并将读指针返回到文件头
	cout << "请输入要检索的单词：";
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
		cout << "文件" << file_name << "里面没有单词" << input_word << endl;
	}
	else {
		vector<int>::iterator i_line_nums = line_nums.begin(),
			i_word_index = word_index.begin(),
			i_amounts = amounts.begin();
		for (; i_line_nums != line_nums.end(); i_line_nums++, i_amounts++) {
			cout << "行号：" << *i_line_nums << ",次数：" << *i_amounts << "起始位置分别为：";
			for (int i = 0; i < *i_amounts; i++) {
				cout << "第" << *i_word_index+1 << "个字符 ";
				i_word_index++;
			}
			cout << endl;
		}
	}
}
void File::locateWordsInLine(string out_line, string input_word, vector<int>& word_index, int &amount, vector<int>& amounts) {
	istringstream out_line_stream(out_line);//创建字符串输入流
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
