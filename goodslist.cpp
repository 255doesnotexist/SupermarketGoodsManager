#include <conio.h>
#include "goodslist.h"

using std::string;
using std::map;
using std::cout;
using std::endl;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::istringstream;

GoodsList::GoodsList(): head(NULL) {} //构造函数
GoodsList::~GoodsList() { //析构函数
    Node* p = head;
    while (p != NULL) {
        Node* q = p->next;
        delete p->data;
        delete p;
        p = q;
    }
}

GoodsList::Node* GoodsList::getHead() {
    return this->head;
}

void GoodsList::insertGoodsAfter(Node* p, Goods* g) { // 在p后边加上商品g
    Node* pG = new Node(g, p, p -> next);
    p -> next = pG;
}

void GoodsList::insertGoodsAtEnd(Goods* g) { //添加商品
    Node* p = head;

    if (head != NULL) {
        while (p -> next != NULL) {
            p = p -> next;
        }
        Node* np = new Node(g, p, p -> next);
        p -> next = np;
    } else {
        head = new Node(g, NULL, NULL);
    }

}
void GoodsList::deleteGoods(Node *p) { //删除商品
    if (p->prev != NULL) {
        p->prev->next = p->next;
    } else {
        head = p->next;
    }
    if (p->next != NULL) {
        p->next->prev = p->prev;
    }
}
void GoodsList::searchAndDeleteGoods(string name, string type) { //删除商品
    Node* p = head;
    while (p != NULL) {
        if (p->data->getName() == name && p -> data -> getCategory() == type) {
            this -> deleteGoods(p);
            cout << "删除商品 \"" << p->data->getName() << "\" 成功。" << endl;
            delete p->data;
            delete p;
            return;
        }
        p = p->next;
    }
    cout << "该商品不存在！" << endl;
}
void GoodsList::modifyGoods(string name) { //修改商品
    Node* p = head;
    while (p != NULL) {
        if (p->data->getName() == name) {
            cout << "请输入新的商品价格：" << endl;
            double price;
            cin >> price;
            p->data->setPrice(price);
            cout << "请输入新的商品库存量：" << endl;
            int stock;
            cin >> stock;
            p->data->setStock(stock);
            cout << "请输入新的商品生产厂家：" << endl;
            string manufacturer;
            cin >> manufacturer;
            p->data->setManufacturer(manufacturer);
            cout << "请输入新的商品品牌：" << endl;
            string brand;
            cin >> brand;
            p->data->setBrand(brand);
            return;
        }
        p = p->next;
    }
    cout << "该商品不存在！" << endl;
}
GoodsList::Node* GoodsList::searchGoodsByName(string name, Node* p) { //查询商品
    // 指定p可以从新地方往下找
    if(p == nullptr) p = head;
    while (p != NULL) {
        if (p->data->getName() == name) {
            return p; // 成功查询到商品信息
        }
        p = p->next;
    }
    cout << "该记录不存在！" << endl;
    return nullptr;
}
GoodsList::Node* GoodsList::searchGoodsByManufacturer(string manufacturer, Node* p) { //查询商品
    // 指定p可以从新地方往下找
    if(p == nullptr) p = head;
    while (p != NULL) {
        if (p->data->getManufacturer() == manufacturer) {
            return p; // 成功查询到商品信息
        }
        p = p->next;
    }
    cout << "该记录不存在！" << endl;
    return nullptr;
}
GoodsList::Node* GoodsList::searchGoodsByCategory(string category, Node* p) { //查询商品
    // 指定p可以从新地方往下找
    if(p == nullptr) p = head;
    while (p != NULL) {
        if (p->data->getCategory() == category) {
            return p; // 成功查询到商品信息
        }
        p = p->next;
    }
    cout << "该记录不存在！" << endl;
    return nullptr;
}
void GoodsList::displayAllGoods() { //显示所有商品
    Node* p = head;
    while (p != NULL) {
        p->data->display();
        p = p->next;
        cout << "======================================" << endl;
        cout << "-         按任意键显示下一条         -" << endl;
        cout << "======================================" << endl;
        fflush(stdin); getch();
    }
}
void GoodsList::saveToFile() { //存储商品信息到文件
    ofstream fout("SupermarketGoods.data");
    Node* p = head;
    while (p != NULL) {
        fout << p->data->toSerializedString() << endl;
        p = p->next;
        if (p == head) break; // 循环链表回到头
    }
    fout.close();
}
void GoodsList::readFromFile() { //从文件中读取商品信息
    ifstream fin("SupermarketGoods.data");

    string info, decoded_info, category;

    while (fin >> info) {
        decoded_info = Base64::decode(info);

        istringstream iss(decoded_info);
        iss >> category;

        if (category == "Food") {
            insertGoodsAtEnd(new Food(info));
        } else if (category == "Cosmetics") {
            insertGoodsAtEnd(new Cosmetics(info));
        } else if (category == "DailyNecessities") {
            insertGoodsAtEnd(new DailyNecessities(info));
        } else if (category == "Beverage") {
            insertGoodsAtEnd(new Beverage(info));
        }
    }
    fin.close();
}
map<string, int> GoodsList::getBrandMap() {
    map<string, int> brandMap;
    GoodsList::Node* p = head;
    while (p != NULL) {
        brandMap[p->data->getBrand()] += p->data->getStock();
        p = p->next;
    }
    return brandMap;
}
map<string, int> GoodsList::getTypeMap() {
    map<string, int> typeMap;
    GoodsList::Node* p = head;
    while (p != NULL) {
        if (p->data->getCategory() == "Food") {
            typeMap["食品"] += p->data->getStock();
        } else if (p->data->getCategory() == "Cosmetics") {
            typeMap["化妆品"] += p->data->getStock();
        } else if (p->data->getCategory() == "DailyNecessities") {
            typeMap["日用品"] += p->data->getStock();
        } else if (p->data->getCategory() == "Beverage") {
            typeMap["饮料"] += p->data->getStock();
        }
        p = p->next;
    }
    return typeMap;
}

size_t GoodsList::length() {
    GoodsList::Node* p = head;
    size_t ret = 0;
    while (p != NULL) {
        ++ret;
        p = p->next;
    }
    return ret;
}
