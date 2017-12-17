#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include "File.h"
using namespace std;

class File;

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


System::System() {
	file_list_head = new File("BlackHeadFile.txt");
	file_list_head->next_file = NULL;
	present_file = file_list_head;
	setOperator();
}
System::~System() {
	present_file = file_list_head;
	while (present_file->next_file != NULL){
		if (remove((present_file->file_name).c_str()) == 0) {
			cout << "ɾ���ɹ���" << endl;
		}
		present_file = present_file->next_file;
	}
	if (remove((present_file->file_name).c_str()) == 0) {
		cout << "ɾ���ɹ���" << endl;
	}
}
File* System::fileExist(string _file_name) {
	File* temp = file_list_head;
	while (temp != NULL) {
		if (temp->file_name == _file_name)
			return temp;
		temp = temp->next_file;
	}
	return NULL;
}
bool System::systemEmpty() {
	if (file_list_head->next_file == NULL) {
		return true;
	}
	return false;
}
void System::setOperator() {
	/*ϵͳ�����棬�����û����в�����ͨ��switch������ѡ����������ڴ������Ҫ���û���������*/
	cout << "***************************************************************" << endl;
	cout << "********************�ı��ļ����ʵļ��������*******************" << endl;
	cout << "����������������������������������������������������������������������������������������������������������������������������" << endl
		<< "��                     ��1�������ı��ĵ�                      ��" << endl
		<< "��                     ��2���ı����ʻ���                      ��" << endl
		<< "��                     ��3�����ʶ�λ                          ��" << endl
		<< "��                     ��4���˳�                              ��" << endl
		<< "����������������������������������������������������������������������������������������������������������������������������" << endl;
	int operate;
	cout << "��ѡ�������1~4��:";
	cin >> operate;

	switch (operate) {
	case 1: {
		setInputFile();
		setOperator();
		break;
	}
	case 2: {
		if(systemEmpty()){
			cout << "��û�д����ļ������ȴ����ļ���" << endl;
			setOperator();
		}else{
			countWords();
			setOperator();
		}
		break;
	}
	case 3: {
		if(systemEmpty()){
			cout << "��û�д����ļ������ȴ����ļ���" << endl;
			setOperator();
		}else{
			locateOrCountWordsInFile();
			setOperator();
		}
		break;
	}
	case 4: {
		break;
	}
	default:
		cout << "������������������ѡ�����." << endl;
		setOperator();
		break;
	}
}
void System::setInputFile() {
	/*ͨ���û������ļ����������ļ���Ҫע�⵱���������Ӻ�׺Ҳ�ǿ��Խ��д򿪡�д��Ȳ����ģ����ǽ��鴴����ʱ��ʹ��".txt"��׺��*/
	cout << "������Ҫ�������ļ�����";
	string _file_name;
	cin >> _file_name;
	while (fileExist(_file_name) != NULL) {
		cout << "�ļ���" << _file_name << " �Ѵ��ڣ������������ļ���:";
		cin >> _file_name;
	}
	File* temp = new File(_file_name);
	present_file = file_list_head;
	while (present_file->next_file != NULL){
		present_file = present_file->next_file;
	}
	present_file->next_file = temp;
	temp->next_file = NULL;
//	printSystem();//��ʱ�鿴System
	inputToFile(_file_name);
	//����Fileʵ����������System�ļ������У�ͬʱҪ���û���ʼ���ļ����������ı���
}
void System::inputToFile(string _file_name) {
	/*���ڳ�ʼ���ļ����ӱ�׼�������ж�ȡ�ַ������ӵ��ļ����У�ͬʱѯ���û��Ƿ�������룬����������������´������������*/
	File* temp = fileExist(_file_name);
	char go_on;
	string input_line;
	cout << "������һ���ı���";
	getline(cin, input_line);
	getline(cin, input_line);
	//��һ��getline�����������������Ļس������ڶ��в����û�������������ı�
	temp->out_file << input_line << endl;
	cout << "���������y or n :";
	cin >> go_on;
	while (go_on != 'y' && go_on != 'n') {
		cout << "�������󣬽��������y or n :";
		cin >> go_on;
	}
	while (go_on == 'n') {
		cout << "������һ���ı���";
		getline(cin, input_line);
		getline(cin, input_line);
		temp->out_file << input_line << endl;
		cout << "���������y or n :";
		cin >> go_on;
	}
	if (go_on == 'y') {
		cout << "�����ļ�����" << endl;
		return;
	}
}
void System::countWords() {
	string _file_name;
	cout << "�������ļ�����";
	cin >> _file_name;
	while (!fileExist(_file_name)) {
		cout << "���ļ������ڣ������������ļ�����";
		cin >> _file_name;
	}
	present_file = fileExist(_file_name);
	present_file->countWords();
}
void System::locateOrCountWordsInFile() {
	/*���û�ѡ�����3���Ӳ���(a��b)����������Ӧ����*/
	char choice;
	cout << "############################################################" << endl;
	cout << "####################�ı��ļ����ʵļ��������################" << endl;
	cout << "�ˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡ�" << endl
		<< "��                 ��a��    ���ʳ��ִ���                    ��" << endl
		<< "��                                                          ��" << endl
		<< "��                 ��b��    ���ʳ���λ��                    ��" << endl
		<< "��                                                          ��" << endl
		<< "�ˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡˡ�" << endl;
	cout << "��ѡ��a��b��";
	cin >> choice;
	while (choice != 'a' && choice != 'b'){
		cout << "����������������루a��b����";
		cin >> choice;
	}
	if (choice == 'a'){
		countWordsInFile();
	}
	else {
		locateWordsInFile();
	}
}
void System::locateWordsInFile() {
	string _file_name;
	cout << "�������ļ�����";
	cin >> _file_name;
	while (!fileExist(_file_name)) {
		cout << "���ļ������ڣ������������ļ�����";
		cin >> _file_name;
	}
	present_file = fileExist(_file_name);
	present_file->locateWordsInFile();
}
void System::countWordsInFile() {
	string _file_name;
	cout << "�������ļ�����";
	cin >> _file_name;
	while (!fileExist(_file_name)) {
		cout << "���ļ������ڣ������������ļ�����";
		cin >> _file_name;
	}
	present_file = fileExist(_file_name);
	present_file->countWordsInFile();
}
void System::printSystem() {
	File* temp = file_list_head;
	cout << "***********************************" << endl;
	while (temp != NULL) {
		cout << temp->file_name << endl;
		temp = temp->next_file;
	}
	cout << "***********************************" << endl;

}
#endif // !SYSTEM_H
