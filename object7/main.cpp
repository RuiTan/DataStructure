#include <fstream>
#include "Woods.h"

int main() {
    int operate = 0;
    cout << "��ѡ�����뷽����0-����̨���룬1-�ļ����룩:";
    cin >> operate;
    while (operate != 0 && operate != 1) {
        cout << "��������������ѡ�����뷽��:";
        cin >> operate;
    }
    if (operate == 0) {
        Woods woods;
    }
    else {
        ifstream in_file("in.txt");
        if (!in_file) {
            cerr << "�޷����ļ���";
            exit(0);
        }
        Woods woods(in_file);
    }
    return 0;
}