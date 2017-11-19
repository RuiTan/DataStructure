//
// Created by tanrui on 17-11-19.
//

#ifndef OBJECT7_WOODS_H
#define OBJECT7_WOODS_H
#define MAXAMOUNT 10000

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
    Wood* mergeWood(Wood *lwood, Wood *rwood);
    void getCost();
    void printWoodsHuffmanTree(Wood *wood);
protected:
    void PreOrder(Wood *current,void (*visit)(Wood *wood));
    void sortWoods();
    bool ifInputValid(string str);//输入是否合理
    int amount;
    Wood* root;
    int* woods;
    bool isOdd;//木头数量是否为奇数
};

#endif //OBJECT7_WOODS_H
