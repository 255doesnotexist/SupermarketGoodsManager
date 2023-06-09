#ifndef BEVERAGE_H
#define BEVERAGE_H

#include "goods.h"

//定义饮料类
class Beverage: public Goods {
private:
    std::string flavor; //饮料口味
public:
    Beverage(std::string n, double p, int s, std::string m, std::string b, std::string f); //构造函数
    Beverage(std::string serialized_string); 
    void display();
    std::string getFlavor();
    void setFlavor(std::string f);
    std::wstring toString();
    std::string toSerializedString();
    void parse(const std::string &data);
    std::string getCategory(){return "Beverage";}
};

#endif
