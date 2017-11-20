#include <fstream>
#include "Woods.h"

int main() {
    int operate = 0;
    cout << "请选择输入方法（0-控制台输入，1-文件输入）:";
    cin >> operate;
    while (operate != 0 && operate != 1) {
        cout << "输入有误，请重新选择输入方法:";
        cin >> operate;
    }
    if (operate == 0) {
        Woods woods;
    }
    else {
        ifstream in_file("in.txt");
        if (!in_file) {
            cerr << "无法打开文件！";
            exit(0);
        }
        Woods woods(in_file);
    }
    system("pause");
    return 0;
}