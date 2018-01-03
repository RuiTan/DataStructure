//
// Created by tanrui on 17-11-19.
//

#ifndef OBJECT7_WOODS_H
#define OBJECT7_WOODS_H
#define MAXAMOUNT 10000
#include <cmath>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
using namespace std;

struct Wood{
    Wood(){};
    Wood(int _length, Wood *l, Wood *r):length(_length),rchild(r),lchild(l){};
    int length;
    Wood *lchild, *rchild;
};

static long cost = 0;

class Woods{
public:
    Woods():amount(0), root(nullptr), woods(nullptr){
        getWoods(cin);
        setWoodsTree();
    };
    Woods(istream &in):amount(0), root(nullptr), woods(nullptr){
        getWoods(in);
        setWoodsTree();
    };
    ~Woods(){
        amount = 0;
        root = nullptr;
        woods = nullptr;
        cost = 0;
    };
    void getWoods(istream &in = cin);
    void setWoodsTree();
    void getCost();
    void printWoodsHuffmanTree(Wood *wood);
protected:
    void PreOrder(Wood *current,void (*visit)(Wood *wood));
    void sortWoods();
    bool ifInputValid(string str);
    Wood* mergeWood(Wood *lwood, Wood *rwood);
    int amount;
    Wood* root;
    int* woods;
    bool isOdd;//木头数量是否为奇数
};

void Woods::getWoods(istream &in) {
    // 从给定的输入端获取本题的主要数据，可为文件输入也可为标准控制台输入
    cout << "请输入要将木头锯成多少块(0-10000)：";
    in >> amount;
    while (amount <= 0 || amount >= MAXAMOUNT) {
        cout << "输入有误，请重新输入：";
        in >> amount;
    }
    // 错误检查，要求输入的amount在0-MAXAMOUNT之间
    woods = (int *)malloc(sizeof(int)*amount);
    // 使用数组来存储用户输入（或者文件输入）的N块木头的长度
    cout << "请依次输入每块木头的长度：";
    string string1;
    getline(in, string1);
    getline(in, string1);
    while (!ifInputValid(string1)) {
        in.clear();
        in.seekg(0);
        cout << "输入有误,请重新依次输入每块木头的长度：";
        getline(in, string1);
    }
    // 错误检查，方法是检测输入中是否含有非空格或者‘0-9’的字符
    istringstream istringstream1(string1);
    for (int i = 0; i < amount; i++) {
        istringstream1 >> woods[i];
        if (woods[i] == 0){
            // 这里出现了输入的木头数量与实际每块木头加起来的数量不等，取后值
            amount = i;
            break;
        }
    }
    // 创建字符串输入流，像数组中读取木头长度
}

void Woods::setWoodsTree() {
    // 通过读入的数组，为Huffman树创建基数组
    sortWoods();
    // 先将数组排序，方便构建Huffman树的基本条件
    if (amount == 1) {
        cout << "你不需要任何花费！\n";
        return;
    }
    // 当只需要1根木头时，那就是不需要砍，花费为0
    isOdd = amount % 2 == 0 ? false : true;
    // 对于用户输入的数组，可能有奇数项和偶数项两种情况，用个变量进行标记，项目文档中会讨论其工作原理
    vector<Wood *> currents(amount / 2 + isOdd);
    //Wood *currents[amount/2+isOdd];
    //一开始在clion中直接使用数组，而转移到vs中，发现vs不支持在声明数组大小时使用非常量参数，就很头疼，于是改用vector存储
    // 之所以选择vector存储，一是因为上一行所述，二是因为algorithm中自带标准容器排序算法，美滋滋
    Wood *currentL, *currentR;
    for (int i = 0; i < amount / 2; i++) {
        currentL = new Wood(woods[2 * i], nullptr, nullptr);
        currentR = new Wood(woods[2 * i + 1], nullptr, nullptr);
        currents[i] = mergeWood(currentL, currentR);
    }
    if (isOdd) {
        currents[amount / 2] = new Wood(woods[amount - 1], nullptr, nullptr);
        sort(currents.begin(), currents.end(), [](Wood *wood1, Wood *wood2) {
            return wood1->length < wood2->length;
        });
        //自定义比较函数（lambda函数），原因在于若是奇数组，可能最后一个数未参与前面的两两相加，而其又并不是Huffman数奇数组中最大的一个，故需排序以获取正确数列
    }
    Wood *currentP = mergeWood(currents[0], currents[1]);
    for (int j = 2; j < amount / 2 + isOdd; j++) {
        currentP = mergeWood(currentP, currents[j]);
    }
    // 一个循环构建Huffman树，事实上，这里构建出的树与标准Huffman树互成镜像，但是原理以及行为啥的都是如出一辙
    root = currentP;
    getCost();
    cout << "最小花费为：" << cost << "RMB!\n";
    // 获取最后的花费
    printWoodsHuffmanTree(root);
    // 将构建出的Huffman树打印出来可通过括号包含关系看出其层次结构
}

bool Woods::ifInputValid(string str) {
    // 用于判定用户输入的字符串是否有效
    string::iterator is = str.begin();
    // 使用iterator迭代器遍历字符串中每个字符
    for (; is != str.end(); ++is) {
        if (*is == ' ' || (*is <= '9' && *is >= '0')) {
            continue;
        }
        else {
            return false;
        }
    }
    return true;
}

void Woods::sortWoods() {
    // 希尔排序算法（直接从项目十中拷过来的）
    int flag = amount, temp, j;
    while (flag != 1) {
        flag = ceil(flag / 3) + 1;
        for (int i = flag; i<amount; i++) {
            if (woods[i]<woods[i - flag]) {
                temp = woods[i], j = i - flag;
                while (j >= 0 && temp < woods[j]) {
                    woods[j + flag] = woods[j];
                    j -= flag;
                }
                woods[j + flag] = temp;
            }
        }
    }
}

Wood* Woods::mergeWood(Wood *lwood, Wood *rwood) {
    // 通过左右子结点构建二叉树
    Wood *parent = new Wood(lwood->length + rwood->length, lwood, rwood);
    return parent;
}

void Woods::PreOrder(Wood *current, void(*visit)(Wood *wood)) {
    // 前序遍历算法（从项目九二叉排序树中拷过来的）
    if (current != nullptr) {
        visit(current);
        PreOrder(current->lchild, visit);
        PreOrder(current->rchild, visit);
    }
}

void Woods::getCost() {
    // 调用前序遍历函数，并创建lambda函数，对于除用户输入的最终木头长度数组外的所有结点进行相加
    PreOrder(root, [](Wood *wood) {
        if (wood->lchild != nullptr && wood->rchild != nullptr) {
            cost += wood->length;
        }
    });
}

void Woods::printWoodsHuffmanTree(Wood *wood) {
    // 也是采用前序遍历方法，对Huffman树进行输出，输出的结果可明显看出构建出的结构
    if (wood != nullptr) {
        cout << wood->length;
        if (wood->lchild != nullptr) {
            cout << "(";
            printWoodsHuffmanTree(wood->lchild);
        }
        if (wood->lchild != nullptr && wood->rchild != nullptr) {
            cout << ",";
            printWoodsHuffmanTree(wood->rchild);
            cout << ")";
        }
    }
}
#endif //OBJECT7_WOODS_H
