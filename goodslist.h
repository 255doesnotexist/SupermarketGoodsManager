#ifndef GOODSLIST_H
#define GOODSLIST_H

#include <iostream>
#include <fstream>
#include <map>

#include "goods.h"
#include "food.h"
#include "cosmetics.h"
#include "dailynecessities.h"
#include "beverage.h"

//定义商品链表类
class GoodsList {
public:
    struct Node { //链表节点
        Goods* data; //指向商品对象的指针
        Node* prev; //指向前一个节点的指针
        Node* next; //指向后一个节点的指针
        Node(Goods* d, Node* p = NULL, Node* n = NULL): data(d), prev(p), next(n) {} //构造函数
    };
private:
    Node* head; //指向链表头节点
public:
    GoodsList(); //构造函数
    ~GoodsList();
    Node* getHead();
    void insertGoodsAfter(Node *p, Goods *g);
    void insertGoodsAtEnd(Goods* g);
    void searchAndDeleteGoods(std::string name, std::string type);
    void deleteGoods(Node *p);
    void modifyGoods(std::string name);
    Node* searchGoodsByName(std::string name, Node* p = nullptr);
    Node* searchGoodsByManufacturer(std::string manufacturer, Node* p = nullptr);
    Node* searchGoodsByCategory(std::string manufacturer, Node* p = nullptr);
    void displayAllGoods();
    void saveToFile();
    void readFromFile();
    size_t length();
    std::map<std::string, int> getBrandMap();
    std::map<std::string, int> getTypeMap();
};

#endif
