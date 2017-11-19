//
// Created by tanrui on 17-11-19.
//

#include <cmath>
#include "Woods.h"

void Woods::getWoods(istream &in){
    cout << "请输入要将木头锯成多少块(0-10000)：";
    in >> amount;
    while (amount <= 0 || amount >= MAXAMOUNT){
        cout << "输入有误，请重新输入：";
        in >> amount;
    }
    woods = (int *)malloc(sizeof(int)*amount);
    cout << "请依次输入每块木头的长度：";
    string string1;
    getline(in, string1);
    getline(in, string1);
    while (!ifInputValid(string1)){
        in.clear();
        in.seekg(0);
        cout << "输入有误,请重新依次输入每块木头的长度：";
        getline(in, string1);
    }
    istringstream istringstream1(string1);
    for (int i = 0; i < amount; i++) {
        istringstream1 >> woods[i];
    }
}
void Woods::setWoodsTree() {
    sortWoods();
    if (amount == 1){
        cout << "最小花费为：" << woods[0] << "RMB!\n";
        return;
    }
    isOdd = amount%2 == 0 ? false : true;
    Wood *currents[amount/2 + isOdd];
    Wood *currentL, *currentR;
    for (int i = 0; i < amount/2; i++) {
        currentL = new Wood(woods[2*i], nullptr, nullptr);
        currentR = new Wood(woods[2*i+1], nullptr, nullptr);
        currents[i] = mergeWood(currentL, currentR);
    }
    if (isOdd){
        currents[amount/2] = new Wood(woods[amount-1], nullptr, nullptr);
    }
    Wood *currentP = mergeWood(currents[0], currents[1]);
    for (int j = 2; j < amount/2 + isOdd; j++) {
        currentP = mergeWood(currentP, currents[j]);
    }
    root = currentP;
    getCost();
    cout << "最小花费为：" << cost << "RMB!\n";
    printWoodsHuffmanTree(root);
}

bool Woods::ifInputValid(string str) {
    string::iterator is = str.begin();
    for (; is != str.end(); ++is) {
        if (*is == ' ' || (*is <= '9' && *is >= '0')){
            continue;
        } else{
            return false;
        }
    }
    return true;
}

void Woods::sortWoods() {
    int flag = amount, temp, j;
    while (flag!=1){
        flag = ceil(flag/3) + 1;
        for (int i = flag; i<amount; i++){
            if (woods[i]<woods[i-flag]){
                temp = woods[i], j = i-flag;
                while (j >= 0 && temp < woods[j]){
                    woods[j+flag] = woods[j];
                    j-=flag;
                }
                woods[j+flag] = temp;
            }
        }
    }
}

Wood* Woods::mergeWood(Wood *lwood, Wood *rwood) {
    Wood *parent = new Wood(lwood->length + rwood->length, lwood, rwood);
    return parent;
}

void Woods::PreOrder(Wood *current, void (* visit)(Wood *wood)){
    if (current != nullptr){
        visit(current);
        PreOrder(current->lchild, visit);
        PreOrder(current->rchild, visit);
    }
}

void Woods::getCost() {
    PreOrder(root, [](Wood *wood){
        if (wood->lchild != nullptr && wood->rchild != nullptr){
            cost += wood->length;
        }
    });
    if (isOdd){
        cost -= woods[amount];
    }
}

void Woods::printWoodsHuffmanTree(Wood *wood) {
    if (wood != nullptr){
        cout << wood->length;
        if (wood->lchild!= nullptr){
            cout << "(";
            printWoodsHuffmanTree(wood->lchild);
        }
        if (wood->lchild!= nullptr && wood->rchild!= nullptr){
            cout << ",";
            printWoodsHuffmanTree(wood->rchild);
            cout << ")";
        }
    }
}