#ifndef GOODS_H
#define GOODS_H

#include "base64.h"
#include "utils.h"

#include <string>
#include <cassert>
#include <sstream>

//定义商品类
class Goods {
    protected:
        std::string name; //商品名称
        double price; //商品价格
        int stock; //商品库存量
        std::string manufacturer; //商品生产厂家
        std::string brand; //商品品牌
    public:
        Goods(std::string n, double p, int s, std::string m, std::string b); //构造函数
        virtual ~Goods() {}
        virtual void display();
        std::string getName();
        double getPrice();
        int getStock();
        std::string getManufacturer();
        std::string getBrand();
        void setPrice(double p);
        void setStock(int s);
        void setManufacturer(std::string m);
        void setName(std::string m);
        void setBrand(std::string b);
        virtual std::wstring toString() = 0;
        virtual std::string toSerializedString() = 0;
        virtual void parse(const std::string &data) = 0;
        virtual std::string getCategory() {
            return "Goods";
        }
};

#endif
