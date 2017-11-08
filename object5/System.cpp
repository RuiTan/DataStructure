#include "System.h"
#include <stdio.h>

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
			cout << "delete succeed" << endl;
		}
		else{
			cout << "delete err" << endl;
		}
		present_file = present_file->next_file;
	}
	if (remove((present_file->file_name).c_str()) == 0) {
		cout << "delete succeed" << endl;
	}
	else {
		cout << "delete err" << endl;
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
	/*系统主界面，导航用户进行操作，通过switch操作符选择操作，对于错误操作要求用户重新输入*/
	cout << "***************************************************************" << endl;
	cout << "********************文本文件单词的检索与计数*******************" << endl;
	cout << "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl
		<< "■                     【1】建立文本文档                    ■" << endl
		<< "■                     【2】文本单词汇总                    ■" << endl
		<< "■                     【3】单词定位                        ■" << endl
		<< "■                     【4】退出                            ■" << endl
		<< "■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■" << endl;
	int operate;
	cout << "请选择操作（1~4）:";
	cin >> operate;

	switch (operate) {
	case 1: {
		setInputFile();
		setOperator();
		break;
	}
	case 2: {
		countWords();
		setOperator();
		break;
	}
	case 3: {
		locateOrCountWordsInFile();
		setOperator();
		break;
	}
	case 4: {
		break;
	}
	default:
//		printSystem();
		cout << "操作输入有误，请重新选择操作." << endl;
		setOperator();
		break;
	}
}
void System::setInputFile() {
	/*通过用户输入文件名来创建文件，要注意当创建若不加后缀也是可以进行打开、写入等操作的，但是建议创建的时候使用".txt"后缀。*/
	cout << "请输入要建立的文件名：";
	string _file_name;
	cin >> _file_name;
	while (fileExist(_file_name) != NULL) {
		cout << "文件：" << _file_name << " 已存在！请重新输入文件名:";
		cin >> _file_name;
	}
	File* temp = new File(_file_name);
	present_file = file_list_head;
	while (present_file->next_file != NULL){
		present_file = present_file->next_file;
	}
	present_file->next_file = temp;
	temp->next_file = NULL;
//	printSystem();//临时查看System
	inputToFile(_file_name);
	//创建File实例，并链入System文件链表中，同时要求用户初始化文件（即输入文本）
}
void System::inputToFile(string _file_name) {
	/*用于初始化文件，从标准输入流中读取字符串并加到文件流中，同时询问用户是否继续输入，若结束输入则进行下次主界面操作。*/
	File* temp = fileExist(_file_name);
	char go_on;
	string input_line;
	cout << "请输入一行文本：";
	getline(cin, input_line);
	getline(cin, input_line);
	//第一行getline用于清空输入流缓存的回车符，第二行才是用户输入的真正的文本
	temp->out_file << input_line << endl;
	cout << "结束输入嘛？y or n :";
	cin >> go_on;
	while (go_on != 'y' && go_on != 'n') {
		cout << "输入有误，结束输入嘛？y or n :";
		cin >> go_on;
	}
	while (go_on == 'n') {
		cout << "请输入一行文本：";
		getline(cin, input_line);
		getline(cin, input_line);
		temp->out_file << input_line << endl;
		cout << "结束输入嘛？y or n :";
		cin >> go_on;
	}
	if (go_on == 'y') {
		cout << "建立文件结束" << endl;
		return;
	}
}
void System::countWords() {
	string _file_name;
	cout << "请输入文件名：";
	cin >> _file_name;
	while (!fileExist(_file_name)) {
		cout << "该文件不存在，请重新输入文件名：";
		cin >> _file_name;
	}
	present_file = fileExist(_file_name);
	present_file->countWords();
}
void System::locateOrCountWordsInFile() {
	/*由用户选择操作3的子操作(a或b)，并进行相应操作*/
	char choice;
	cout << "###############################################################" << endl;
	cout << "####################文本文件单词的检索与计数###################" << endl;
	cout << "∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷" << endl
		<< "∷                 【a】    单词出现次数                    ∷" << endl
		<< "∷                                                          ∷" << endl
		<< "∷                 【b】    单词出现位置                    ∷" << endl
		<< "∷                                                          ∷" << endl
		<< "∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷∷" << endl;
	cout << "请选择a或b：";
	cin >> choice;
	while (choice != 'a' && choice != 'b'){
		cout << "输入错误，请重新输入（a或b）：";
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
	cout << "请输入文件名：";
	cin >> _file_name;
	while (!fileExist(_file_name)) {
		cout << "该文件不存在，请重新输入文件名：";
		cin >> _file_name;
	}
	present_file = fileExist(_file_name);
	present_file->locateWordsInFile();
}
void System::countWordsInFile() {
	string _file_name;
	cout << "请输入文件名：";
	cin >> _file_name;
	while (!fileExist(_file_name)) {
		cout << "该文件不存在，请重新输入文件名：";
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