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
    bool isOdd;//ľͷ�����Ƿ�Ϊ����
};

void Woods::getWoods(istream &in) {
    // �Ӹ���������˻�ȡ�������Ҫ���ݣ���Ϊ�ļ�����Ҳ��Ϊ��׼����̨����
    cout << "������Ҫ��ľͷ��ɶ��ٿ�(0-10000)��";
    in >> amount;
    while (amount <= 0 || amount >= MAXAMOUNT) {
        cout << "�����������������룺";
        in >> amount;
    }
    // �����飬Ҫ�������amount��0-MAXAMOUNT֮��
    woods = (int *)malloc(sizeof(int)*amount);
    // ʹ���������洢�û����루�����ļ����룩��N��ľͷ�ĳ���
    cout << "����������ÿ��ľͷ�ĳ��ȣ�";
    string string1;
    getline(in, string1);
    getline(in, string1);
    while (!ifInputValid(string1)) {
        in.clear();
        in.seekg(0);
        cout << "��������,��������������ÿ��ľͷ�ĳ��ȣ�";
        getline(in, string1);
    }
    // �����飬�����Ǽ���������Ƿ��зǿո���ߡ�0-9�����ַ�
    istringstream istringstream1(string1);
    for (int i = 0; i < amount; i++) {
        istringstream1 >> woods[i];
        if (woods[i] == 0){
            // ��������������ľͷ������ʵ��ÿ��ľͷ���������������ȣ�ȡ��ֵ
            amount = i;
            break;
        }
    }
    // �����ַ������������������ж�ȡľͷ����
}

void Woods::setWoodsTree() {
    // ͨ����������飬ΪHuffman������������
    sortWoods();
    // �Ƚ��������򣬷��㹹��Huffman���Ļ�������
    if (amount == 1) {
        cout << "�㲻��Ҫ�κλ��ѣ�\n";
        return;
    }
    // ��ֻ��Ҫ1��ľͷʱ���Ǿ��ǲ���Ҫ��������Ϊ0
    isOdd = amount % 2 == 0 ? false : true;
    // �����û���������飬�������������ż��������������ø��������б�ǣ���Ŀ�ĵ��л������乤��ԭ��
    vector<Wood *> currents(amount / 2 + isOdd);
    //Wood *currents[amount/2+isOdd];
    //һ��ʼ��clion��ֱ��ʹ�����飬��ת�Ƶ�vs�У�����vs��֧�������������Сʱʹ�÷ǳ����������ͺ�ͷ�ۣ����Ǹ���vector�洢
    // ֮����ѡ��vector�洢��һ����Ϊ��һ��������������Ϊalgorithm���Դ���׼���������㷨��������
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
        //�Զ���ȽϺ�����lambda��������ԭ���������������飬�������һ����δ����ǰ���������ӣ������ֲ�����Huffman��������������һ�������������Ի�ȡ��ȷ����
    }
    Wood *currentP = mergeWood(currents[0], currents[1]);
    for (int j = 2; j < amount / 2 + isOdd; j++) {
        currentP = mergeWood(currentP, currents[j]);
    }
    // һ��ѭ������Huffman������ʵ�ϣ����ﹹ�����������׼Huffman�����ɾ��񣬵���ԭ���Լ���Ϊɶ�Ķ������һ��
    root = currentP;
    getCost();
    cout << "��С����Ϊ��" << cost << "RMB!\n";
    // ��ȡ���Ļ���
    printWoodsHuffmanTree(root);
    // ����������Huffman����ӡ������ͨ�����Ű�����ϵ�������νṹ
}

bool Woods::ifInputValid(string str) {
    // �����ж��û�������ַ����Ƿ���Ч
    string::iterator is = str.begin();
    // ʹ��iterator�����������ַ�����ÿ���ַ�
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
    // ϣ�������㷨��ֱ�Ӵ���Ŀʮ�п������ģ�
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
    // ͨ�������ӽ�㹹��������
    Wood *parent = new Wood(lwood->length + rwood->length, lwood, rwood);
    return parent;
}

void Woods::PreOrder(Wood *current, void(*visit)(Wood *wood)) {
    // ǰ������㷨������Ŀ�Ŷ����������п������ģ�
    if (current != nullptr) {
        visit(current);
        PreOrder(current->lchild, visit);
        PreOrder(current->rchild, visit);
    }
}

void Woods::getCost() {
    // ����ǰ�����������������lambda���������ڳ��û����������ľͷ��������������н��������
    PreOrder(root, [](Wood *wood) {
        if (wood->lchild != nullptr && wood->rchild != nullptr) {
            cost += wood->length;
        }
    });
}

void Woods::printWoodsHuffmanTree(Wood *wood) {
    // Ҳ�ǲ���ǰ�������������Huffman���������������Ľ�������Կ����������Ľṹ
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
