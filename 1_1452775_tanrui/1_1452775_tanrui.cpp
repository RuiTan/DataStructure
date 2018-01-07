#include "ExamineeList.h"
#include <fstream>

int main() {	
	ifstream infile("students.txt");
	ExamineeList list(infile);
	return 0;
}