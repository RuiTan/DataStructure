#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include "File.h"
using namespace std;

class System {
    friend class File;

public:
	System();
	~System();

	File* fileExist(string _file_name);
	bool systemEmpty();
	void setOperator();
	void setInputFile();
	void inputToFile(string _file_name);
	void countWords();
	void locateOrCountWordsInFile();
	void locateWordsInFile();
	void countWordsInFile();
	void printSystem();

private:
	File* file_list_head;
	File* present_file;
};

#endif // !SYSTEM_H
